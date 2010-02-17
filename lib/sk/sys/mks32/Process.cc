/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/StringArray.h>
#include <sk/util/Container.h>
#include <sk/util/Pathname.h>
#include <sk/util/PropertyRegistry.h>
#include <sk/util/Holder.cxx>
#include <sk/util/ArrayList.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/SystemException.h>
#include <sk/rt/Environment.h>

#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/ProcessLaunchException.h>
#include <sk/sys/StreamPortal.h>
#include <sk/io/NullDevice.h>
#include <sk/io/FileDescriptorStream.h>
#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Locker.h>

#include <sk/util/inspect.h>
#include <nutc.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

namespace {
  sk::util::Holder<sk::rt::Mutex> __mutexHolder;
}

struct sk::sys::Process::Implementation
  : public virtual sk::util::Object
{
  Implementation()
    : status(0) {}

  int status;
};

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, sk::util::StringArray());
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline)
  : _scope(*this), _listener(*this)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(cmdline);
}

sk::sys::Process::
Process(ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(sk::util::StringArray());
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline)
  : _scope(*this), _listener(*this)
{
  start(cmdline);
}

sk::sys::Process::
~Process()
{
  if(_detached == false) {
    sk::util::Exception::guard(_scope.warning(SK_METHOD), *this, &sk::sys::Process::stop);
  }
}

void 
sk::sys::Process::
setup()
{
  if(__mutexHolder.isEmpty() == true) {
    __mutexHolder.set(new sk::rt::Mutex);
  }
}

void 
sk::sys::Process::
reset()
{
  __mutexHolder.clear();
}

const sk::util::Class
sk::sys::Process::
getClass() const
{
  return sk::util::Class("sk::sys::Process");
}

int
sk::sys::Process::
getPid() const
{
  return _pid;
}

namespace {
  struct Configurator : public virtual sk::sys::ProcessConfigurator {
    Configurator(const sk::rt::Scope& scope, sk::util::PropertyRegistry& environment) 
      : _scope(scope), _environment(environment), isProcessGroup(false), isConsole(true) {}

    void setEnvironment(const sk::util::String& name, const sk::util::String& value) {
      _environment.setProperty(name, value);
    }

    void setInputStream(const sk::io::InputStream& stream) {
      inputStreamHolder.set(new sk::io::FileDescriptorStream(stream));
    }

    void setOutputStream(const sk::io::OutputStream& stream) {
      outputStreamHolder.set(new sk::io::FileDescriptorStream(stream));
    }

    void setErrorOutputStream(const sk::io::OutputStream& stream) {
      errorStreamHolder.set(new sk::io::FileDescriptorStream(stream));
    }

    void addStream(const sk::io::Stream& stream) {
      _streams.add(sk::util::covariant<sk::io::Stream>(stream.clone()));
    }

    void startProcessGroup(bool state) {
      isProcessGroup = state;
    }

    void keepConsole(bool state) {
      isConsole = state;
    }

    void finalize() {
      sk::sys::StreamPortal::clear();
      sk::sys::StreamPortal::exportStreams(_streams, _environment);
    }

    bool isConsole;
    bool isProcessGroup;
    sk::util::Holder<sk::io::FileDescriptorStream> inputStreamHolder;
    sk::util::Holder<sk::io::FileDescriptorStream> outputStreamHolder;
    sk::util::Holder<sk::io::FileDescriptorStream> errorStreamHolder;

    private:
      const sk::rt::Scope& _scope;
      sk::util::PropertyRegistry& _environment;
      sk::util::ArrayList<sk::io::Stream> _streams;
  };

  struct ExecArgumentCollector : public virtual sk::util::Processor<const sk::util::String> {
    ExecArgumentCollector(std::vector<char*>& arguments)
      : _arguments(arguments) {}

    void process(const sk::util::String& item) const {
      _arguments.push_back(const_cast<char*>(item.getChars()));
    }
    std::vector<char*>& _arguments;
  };

  int start_process_with_redirect(const Configurator& configurator, const sk::rt::Environment& environment, const sk::util::StringArray& cmdline) {
    sk::rt::Locker locker(__mutexHolder.getMutable());

    std::vector<char*> arguments;
    cmdline.forEach(ExecArgumentCollector(arguments));
    arguments.push_back(0);

    std::vector<char> environment_block;
    std::vector<char*> environment_references = environment.serialize(environment_block);

    sk::io::LooseFileDescriptor stdinDescriptor(0);
    sk::io::LooseFileDescriptor stdoutDescriptor(1);
    sk::io::LooseFileDescriptor stderrDescriptor(2);

    sk::io::FileDescriptor savedStdinDescriptor(stdinDescriptor.duplicateLoose().getFileNumber());
    sk::io::FileDescriptor savedStdoutDescriptor(stdoutDescriptor.duplicateLoose().getFileNumber());
    sk::io::FileDescriptor savedStderrDescriptor(stderrDescriptor.duplicateLoose().getFileNumber());

    if(configurator.inputStreamHolder.isEmpty() == false) {
      stdinDescriptor.reopen(configurator.inputStreamHolder.get().getFileDescriptor());
    }
    if(configurator.outputStreamHolder.isEmpty() == false) {
      stdoutDescriptor.reopen(configurator.outputStreamHolder.get().getFileDescriptor());
    }
    if(configurator.errorStreamHolder.isEmpty() == false) {
      stderrDescriptor.reopen(configurator.errorStreamHolder.get().getFileDescriptor());
    }

    int pid = ::_NutForkExecvpe(arguments[0], &arguments[0], &environment_references[0]);

    stdinDescriptor.reopen(savedStdinDescriptor);
    stdoutDescriptor.reopen(savedStdoutDescriptor);
    stderrDescriptor.reopen(savedStderrDescriptor);

    return pid;
  }
}

sk::sys::Process::Implementation&
sk::sys::Process::
process() const
{
  return _implementationHolder.getMutable();
}

void
sk::sys::Process::
start(const sk::util::StringArray& args)
{
  sk::io::NullDevice null;
  start(null.inputStream(), args);
}

void
sk::sys::Process::
start(sk::io::InputStream& inputStream, const sk::util::StringArray& args)
{
  if(args.isEmpty() == true) {
    throw sk::util::UnsupportedOperationException("Non-exec processes not supported on Windowns");
  }
  sk::util::StringArray cmdline = args;
  cmdline.set(0, sk::util::Pathname(cmdline.get(0), "exe").toString());
  _implementationHolder.set(new Implementation);
  _scope.notice("start") << cmdline.inspect();

  _detached = false;
  _running = false;

  try {
    sk::rt::Environment environment;
    Configurator configurator(_scope, environment);
    configurator.setInputStream(inputStream);

    _listener.processConfiguring(configurator);
    configurator.finalize();

    if(configurator.isProcessGroup == true) {
      _scope.warning() << "Process groups not supported";
    }

    if(configurator.isConsole == false) {
      _scope.warning() << "Detach from console not supported";
    }

    _pid = start_process_with_redirect(configurator, environment, cmdline);

    if(_pid < 0) {
      throw sk::rt::SystemException("_NutForkExec");
    }
    _running = true;
    inputStream.close();
  }
  catch(const std::exception& exception) {
    throw sk::sys::ProcessLaunchException(exception.what(), cmdline);
  }
}

void
sk::sys::Process::
processStarting(sk::io::Stream& umbilical)
{
}

int
sk::sys::Process::
processStopping()
{
  return 0;
}

namespace {
  struct Cleaner : public virtual sk::rt::Runnable {
    Cleaner(int pid, int signal, int tolerance) : _pid(pid), _tolerance(tolerance), _canceled(false) {
      terminate(signal);
    }
    void run() {
      for(int counter = _tolerance*10; counter ;--counter) {
        if(_canceled == true) {
          return;
        }
        sk::rt::Thread::sleep(100);
      }
      terminate(SIGKILL);
    }
    void terminate(int signal) {
      if(::kill(_pid, signal) < 0) {
        if(errno != ESRCH) {
          throw sk::rt::SystemException("kill:" + sk::util::String::valueOf(_pid) + ":" + sk::util::String::valueOf(signal));
        }
      }
    }
    void cancel() {
      _canceled = true;
    }
    volatile bool _canceled;
    int _pid;
    int _tolerance;
  };
}

void
sk::sys::Process::
stop() 
{
  if(_running == false) {
    return;
  }
  _listener.processStopping();

  Cleaner cleaner(_pid, SIGKILL, 3);
  sk::rt::Thread terminator(cleaner);

  terminator.start();
  join();
  
  cleaner.cancel();
  terminator.join();
}

void
sk::sys::Process::
kill()
{
  if(isAlive() == false) {
    return;
  }
  Cleaner cleaner(_pid, SIGKILL, 0);
}


void
sk::sys::Process::
processJoining() 
{
}

void
sk::sys::Process::
join()
{
  sk::rt::Locker locker(_mutex);
  if(_running == false) {
    return;
  }
  _listener.processJoining();

  while(true) {
    int status = 0;
    int result = ::waitpid(_pid, &status, 0);

    if(result < 0) {
      if(errno == EINTR) {
        continue;
      }
      if(errno == ECHILD) {
        _scope.debug("ATTN") << sk::rt::SystemException("waitpid:" + sk::util::String::valueOf(_pid)).what();
        break;
      }
      throw sk::rt::SystemException("waitpid:" + sk::util::String::valueOf(_pid));
    }
    if(result == _pid) {
      process().status = status;
      break;
    }
    throw sk::util::IllegalStateException("waitpid:mismatch:" + sk::util::String::valueOf(result) + ":" + sk::util::String::valueOf(_pid));
  }
  _running = false;
}

void
sk::sys::Process::
detach()
{
  _detached = true;
}

bool
sk::sys::Process::
isSuccess() const
{
  return isExited() && exitStatus() == 0;
}

bool
sk::sys::Process::
isExited() const
{
  return isKilled() == false;
}

bool
sk::sys::Process::
isKilled() const
{
  ensureNotRunning();
  return WIFSIGNALED(process().status) ? true : false;
}

void
sk::sys::Process::
ensureNotRunning() const
{
  if(_running == true) {
    throw sk::util::IllegalStateException("Process " + sk::util::String::valueOf(_pid) + " not stopped or joined yet");
  }
}

int
sk::sys::Process::
exitStatus() const
{
  if(isExited() == false) {
    throw sk::util::IllegalStateException("Process killed, not exited");
  }
  return WEXITSTATUS(process().status);
}

int
sk::sys::Process::
signal() const
{
  if(isKilled() == false) {
    throw sk::util::IllegalStateException("Process exited, not killed");
  }
  return WTERMSIG(process().status);
}

bool
sk::sys::Process::
isAlive() const
{
  return _running == true;
}


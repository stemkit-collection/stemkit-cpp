/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/StringArray.h>
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
#include <sk/io/EOFException.h>
#include <sk/io/FileDescriptorStream.h>
#include <sk/io/NullDevice.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Locker.cxx>
#include <sk/rt/scope/Arbitrator.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>

struct sk::sys::Process::Implementation {
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
}

void 
sk::sys::Process::
reset()
{
}

sk::sys::Process::Implementation&
sk::sys::Process::
process() const
{
  return _implementationHolder.get();
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
  struct ExecArgumentCollector : public virtual sk::util::Processor<const sk::util::String> {
    ExecArgumentCollector(std::vector<char*>& arguments)
      : _arguments(arguments) {}

    void process(const sk::util::String& item) const {
      _arguments.push_back(const_cast<char*>(item.getChars()));
    }
    std::vector<char*>& _arguments;
  };
}

namespace {
  struct Configurator : public virtual sk::sys::ProcessConfigurator {
    Configurator(const sk::rt::Scope& scope, sk::util::PropertyRegistry& environment)
      : _scope(scope), _environment(environment), isProcessGroup(false), isConsole(true) {}

    void setEnvironment(const sk::util::String& name, const sk::util::String& value) {
      _environment.setProperty(name, value);
    }

    void setInputStream(const sk::io::InputStream& stream) {
      setStream(0, stream);
    }

    void setOutputStream(const sk::io::OutputStream& stream) {
      setStream(1, stream);
    }

    void setErrorOutputStream(const sk::io::OutputStream& stream) {
      setStream(2, stream);
    }

    void addStream(const sk::io::Stream& stream) {
      _streams.add(sk::util::covariant<sk::io::Stream>(stream.clone()));
    }

    void setStream(int target, const sk::io::Stream& stream) {
      sk::io::LooseFileDescriptor target_descriptor(target);
      sk::io::LooseFileDescriptor source_descriptor(sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor());
      if(source_descriptor.getFileNumber() != target) {
        target_descriptor.reopen(source_descriptor);
      }
      target_descriptor.inheritable(true);
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

    bool isProcessGroup;
    bool isConsole;

    private:
      const sk::rt::Scope& _scope;
      sk::util::PropertyRegistry& _environment;
      sk::util::ArrayList<const sk::io::Stream> _streams;
  };
}

void
sk::sys::Process::
start(const sk::util::StringArray& cmdline)
{
  sk::io::NullDevice null;
  start(null.inputStream(), cmdline);
}

void
sk::sys::Process::
start(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline)
{
  _implementationHolder.set(new Implementation);

  _detached = false;
  _running = false;

  sk::io::AnonymousPipe pipe;
  sk::rt::Locker<sk::rt::scope::Arbitrator> locker(sk::rt::Scope::controller().getAggregator().getArbitrator());
  _pid = fork();

  if(_pid < 0) {
    throw sk::rt::SystemException("fork");
  }
  if(_pid == 0) {
    locker.unlock();
    pipe.closeInput();

    try {
      sk::rt::Environment environment;
      Configurator configurator(_scope, environment);
      configurator.setInputStream(inputStream);
      inputStream.close();

      _listener.processConfiguring(configurator);
      configurator.finalize();
      environment.install();

      if(configurator.isProcessGroup == true || configurator.isConsole == false) {
        ::setsid();
      }
      pipe.closeOutput();
      _listener.processStarting();
      _scope.notice("start") << cmdline.inspect();

      if(cmdline.empty() == false) {
        std::vector<char*> arguments;
        cmdline.forEach(ExecArgumentCollector(arguments));
        arguments.push_back(0);

        // TODO: When ability to expand executable path via PATH environment
        // variable is implemented, this block should be uncommented and used
        // instead of ::execvp() invocation.
        //
        // std::vector<char> environment_block;
        // std::vector<char*> environment_references = environment.serialize(environment_block);
        // ::execve(sk::util::Pathname(arguments[0]).expand(environment.getPath()), &arguments[0], &environment_references[0]);

        ::execvp(arguments[0], &arguments[0]);
        throw sk::rt::SystemException("exec");
      }
    }
    catch(const std::exception& exception) {
      _listener.processFailing(exception.what());
      _scope.notice("fork") << sk::sys::ProcessLaunchException(exception.what(), cmdline).what();
    }
    _exit(99);
  }
  pipe.closeOutput();
  try {
    pipe.inputStream().read();
  }
  catch(const sk::io::EOFException& exception) {}

  _running = true;
  inputStream.close();
}

void
sk::sys::Process::
processStarting()
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

  Cleaner cleaner(_pid, SIGTERM, 3);
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
  sk::rt::Locker<sk::rt::Mutex> locker(_mutex);
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
  ensureNotRunning();
  return WIFEXITED(process().status) ? true : false;
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
  return _running == true && ::kill(_pid, 0) == 0;
}


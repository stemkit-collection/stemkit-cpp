/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <sk/util/Container.h>
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
#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Locker.cxx>

#include <sk/util/inspect.h>

#include <map>
#include <winnutc.h>

struct sk::sys::Process::Implementation {
  HANDLE handle;
  bool isTerminated;
  int exitCode;
};

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::Strings& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, sk::util::Strings());
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::Strings& cmdline)
  : _scope(*this), _listener(*this)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(const sk::util::Strings& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(cmdline);
}

sk::sys::Process::
Process(ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(sk::util::Strings());
}

sk::sys::Process::
Process(const sk::util::Strings& cmdline)
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
    Configurator(const sk::rt::Scope& scope, sk::util::PropertyRegistry& environment) : _scope(scope), _environment(environment) {
      inputHandle = ::GetStdHandle(STD_INPUT_HANDLE);
      outputHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
      errorOutputHandle = ::GetStdHandle(STD_ERROR_HANDLE);

      isProcessGroup = false;
      isConsole = true;
    }

    void setEnvironment(const sk::util::String& name, const sk::util::String& value) {
      _environment.setProperty(name, value);
    }

    void setInputStream(const sk::io::InputStream& stream) {
      inputHandle = toHandle(stream);
    }

    void setOutputStream(const sk::io::OutputStream& stream) {
      outputHandle = toHandle(stream);
    }

    void setErrorOutputStream(const sk::io::OutputStream& stream) {
      errorOutputHandle = toHandle(stream);
    }

    void addStream(const sk::io::Stream& stream) {
      _streams.add(sk::util::covariant<sk::io::Stream>(stream.clone()));
    }

    HANDLE toHandle(const sk::io::Stream& stream) {
      sk::io::LooseFileDescriptor descriptor = sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor();
      HANDLE handle = ::_NutFdToHandle(descriptor.getFileNumber());

      return handle;
    }

    void makeInheritable(HANDLE handle) {
      if(SetHandleInformation(handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT) == 0) {
        throw sk::rt::SystemException("SetHandleInformation");
      }
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

      makeInheritable(inputHandle);
      makeInheritable(outputHandle);
      makeInheritable(errorOutputHandle);
    }

    HANDLE inputHandle;
    HANDLE outputHandle;
    HANDLE errorOutputHandle;
    bool isConsole;
    bool isProcessGroup;

    private:
      const sk::rt::Scope& _scope;
      sk::util::PropertyRegistry& _environment;
      sk::util::ArrayList<const sk::io::Stream> _streams;
  };

  struct CommandLineBuilder : public virtual sk::util::Processor<const sk::util::String> {
    CommandLineBuilder(sk::util::Strings& cmdline)
      : _cmdline(cmdline) {}

    void process(const sk::util::String& item) const {
      _cmdline << item.inspect();
    }
    sk::util::Strings& _cmdline;
  };
}

sk::sys::Process::Implementation&
sk::sys::Process::
process() const
{
  return _implementationHolder.get();
}

void
sk::sys::Process::
start(const sk::util::Strings& args)
{
  sk::io::NullDevice null;
  start(null.inputStream(), args);
}

void
sk::sys::Process::
start(sk::io::InputStream& inputStream, const sk::util::Strings& args)
{
  if(args.isEmpty() == true) {
    throw sk::util::UnsupportedOperationException("Non-exec processes not supported on Windowns");
  }
  _implementationHolder.set(new Implementation);

  sk::util::Strings cmdline;
  args.forEach(CommandLineBuilder(cmdline));

  _scope.notice("start") << cmdline.join(", ");

  _detached = false;
  _running = false;

  try {
    sk::rt::Environment environment;
    Configurator configurator(_scope, environment);
    configurator.setInputStream(inputStream);

    _listener.processConfiguring(configurator);
    configurator.finalize();

    std::vector<char> environment_block;
    environment.serialize(environment_block);

    DWORD process_creation_flags = 0;
    if(configurator.isProcessGroup == true) {
      process_creation_flags |= CREATE_NEW_PROCESS_GROUP;
      _scope.notice() << "New process group will be created";
    }
    if(configurator.isConsole == false) {
      process_creation_flags |= DETACHED_PROCESS;
      _scope.notice() << "Console will be detached";
    }
    PROCESS_INFORMATION process_info = { 0 };
    STARTUPINFO startup_info = { 0 };
    startup_info.cb = sizeof(STARTUPINFO);

    startup_info.hStdInput = configurator.inputHandle;
    startup_info.hStdOutput = configurator.outputHandle;
    startup_info.hStdError = configurator.errorOutputHandle;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;

    sk::util::String cs = cmdline.join(" ");
    sk::util::Container cv(cs.getChars(), cs.size() + 1);

    BOOL status = CreateProcess(0, &cv.at(0), 0, 0, TRUE, process_creation_flags, &environment_block.at(0), 0, &startup_info, &process_info);
    if(status == FALSE) {
      throw sk::rt::SystemException("CreateProcess");
    }
    _pid = process_info.dwProcessId;
    process().handle = process_info.hProcess;
    CloseHandle(process_info.hThread);

    _running = true;
    inputStream.close();
  }
  catch(const std::exception& exception) {
    throw sk::sys::ProcessLaunchException(exception.what(), cmdline);
  }
  _scope.detail("SUCCESS") << args.inspect();
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
    Cleaner(HANDLE process, int tolerance) : _process(process), _tolerance(tolerance), _canceled(false) {
      terminate(tolerance>0 ? true : false);
    }
    void run() {
      for(int counter = _tolerance*10; counter ;--counter) {
        if(_canceled == true) {
          return;
        }
        sk::rt::Thread::sleep(100);
      }
      terminate(false);
    }

    void terminate(bool graceful) {
      if(graceful == false) {
        if(TerminateProcess(_process, 43195) == FALSE) {
          throw sk::rt::SystemException("TerminateProcess");
        }
      }
    }

    void cancel() {
      _canceled = true;
    }

    volatile bool _canceled;
    HANDLE _process;
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

  Cleaner cleaner(process().handle, 3);
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
  Cleaner cleaner(process().handle, 0);
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

  if(WaitForSingleObject(process().handle, INFINITE) == WAIT_FAILED) {
    throw sk::rt::SystemException("WaitForSingleObject");
  }
  DWORD status;
  if(GetExitCodeProcess(process().handle, &status) == FALSE) {
    throw sk::rt::SystemException("GetExitCodeProcess");
  }
  _scope.detail("STATUS") << status;

  process().isTerminated = (status==43195 || status==126 ? true : false);
  process().exitCode = status;

  CloseHandle(process().handle);
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
  return process().isTerminated ? true : false;
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
  return process().exitCode;
}

int
sk::sys::Process::
signal() const
{
  if(isKilled() == false) {
    throw sk::util::IllegalStateException("Process exited, not killed");
  }
  return 9;
}

bool
sk::sys::Process::
isAlive() const
{
  return _running == true;
}


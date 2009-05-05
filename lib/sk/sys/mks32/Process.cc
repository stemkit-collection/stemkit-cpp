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
#include <sk/util/PropertyRegistry.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/SystemException.h>
#include <sk/rt/Environment.h>

#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/ProcessLaunchException.h>
#include <sk/io/FileDescriptorStream.h>
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
      : _scope(scope), _environment(environment) {}

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
      int target = _descriptors.size() + 3;
      setStream(target, stream);

      _descriptors << sk::util::String::valueOf(target);
    }

    void setStream(int target, const sk::io::Stream& stream) {
      _streams.insert(std::make_pair(target, sk::io::FileDescriptorStream(stream)));
    }

    void finalize() {
      if(_descriptors.isEmpty() == false) {
        setEnvironment("SK_STREAMS", _descriptors.join("|"));
      }
    }

    const sk::io::FileDescriptorStream& stream(int descriptor) const {
      stream_container_type::const_iterator iterator = _streams.find(descriptor);
      if(iterator == _streams.end()) {
        throw sk::util::IllegalStateException(sk::util::String::valueOf(descriptor) + ":stream not found");
      }
      return iterator->second;
    }

    typedef std::map<int, const sk::io::FileDescriptorStream> stream_container_type;
    stream_container_type _streams;
    sk::util::StringArray _descriptors;
    const sk::rt::Scope& _scope;
    sk::util::PropertyRegistry& _environment;
  };

  struct CommandLineBuilder : public virtual sk::util::Processor<const sk::util::String> {
    CommandLineBuilder(sk::util::StringArray& cmdline)
      : _cmdline(cmdline) {}

    void process(const sk::util::String& item) const {
      _cmdline << item.inspect();
    }
    sk::util::StringArray& _cmdline;
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
  _implementationHolder.set(new Implementation);

  sk::util::StringArray cmdline;
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

    PROCESS_INFORMATION process_info = { 0 };
    STARTUPINFO startup_info = { 0 };
    startup_info.cb = sizeof(STARTUPINFO);

    startup_info.hStdInput = ::_NutFdToHandle(configurator.stream(0).getFileDescriptor().getFileNumber());
    try {
      startup_info.hStdOutput = _NutFdToHandle(configurator.stream(1).getFileDescriptor().getFileNumber());
    }
    catch(const sk::util::IllegalStateException& exception) {
      _scope.notice("STDOUT") << "Oops, not set -- using default";
      startup_info.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    try {
      startup_info.hStdError = _NutFdToHandle(configurator.stream(2).getFileDescriptor().getFileNumber());
    }
    catch(const sk::util::IllegalStateException& exception) {
      _scope.notice("STDERR") << "Oops, not set -- using default";
      startup_info.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    }

    for(int fd=0; fd<1024 ;++fd) {
      HANDLE handle = _NutFdToHandle(fd);
      SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);
    }
    SetHandleInformation(startup_info.hStdInput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(startup_info.hStdOutput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(startup_info.hStdError, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

    startup_info.dwFlags |= STARTF_USESTDHANDLES;

    sk::util::String cs = cmdline.join(" ");
    sk::util::Container cv(cs.getChars(), cs.size() + 1);
    BOOL status = CreateProcess(0, &cv.at(0), 0, 0, TRUE, 0, &environment_block.at(0), 0, &startup_info, &process_info);
    if(status == FALSE) {
      throw sk::rt::SystemException("CreateProces");
    }
    _pid = process_info.dwProcessId;
    process().handle = process_info.hProcess;
    CloseHandle(process_info.hThread);

    _running = true;
    inputStream.close();
  }
  catch(const std::exception& exception) {
    throw sk::sys::ProcessLaunchException(exception.what(), cmdline).what();
  }
  _scope.detail("SUCCESS") << args.inspect();
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


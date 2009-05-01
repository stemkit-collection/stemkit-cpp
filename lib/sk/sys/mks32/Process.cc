/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/StringArray.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/SystemException.h>

#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/ProcessLaunchException.h>
#include <sk/io/FileDescriptorStream.h>
#include <sk/io/FileInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Locker.cxx>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>

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
  start(defaultInputStream(), cmdline);
}

sk::sys::Process::
Process(ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(defaultInputStream(), sk::util::StringArray());
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline)
  : _scope(*this), _listener(*this)
{
  start(defaultInputStream(), cmdline);
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
  struct ExecArgumentCollector : public virtual sk::util::Processor<const sk::util::String> {
    ExecArgumentCollector(std::vector<char*>& arguments)
      : _arguments(arguments) {}

    void process(const sk::util::String& item) const {
      _arguments.push_back(const_cast<char*>(item.getChars()));
    }
    std::vector<char*>& _arguments;
  };
}

sk::io::InputStream&
sk::sys::Process::
defaultInputStream()
{
  _defaultInputStreamHolder.set(new sk::io::FileInputStream("/dev/null"));
  return _defaultInputStreamHolder.get();
}

namespace {
  struct Configurator : public virtual sk::sys::ProcessConfigurator {
    Configurator(const sk::rt::Scope& scope)
      : _scope(scope) {}

    void setEnvironment(const sk::util::String& name, const sk::util::String& value) {
      sk::util::String entry = name.trim() + "=" + value;
      char* s = new char[entry.length() + 1];
      ::strcpy(s, entry.getChars());
      ::putenv(s);
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
      int fd;
      {
        sk::io::FileDescriptorStream fds(stream);
        fd = ::dup(fds.getFileDescriptor().getFileNumber());
      }
      if(fd != target) {
        ::dup2(fd, target);
        ::close(fd);
      }
    }

    void finalize() {
      if(_descriptors.isEmpty() == false) {
        setEnvironment("SK_STREAMS", _descriptors.join("|"));
      }
    }
    sk::util::StringArray _descriptors;
    const sk::rt::Scope& _scope;
  };
}

void
sk::sys::Process::
start(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline)
{
  _detached = false;
  _running = false;

  _pid = fork();

  if(_pid < 0) {
    throw sk::rt::SystemException("fork");
  }
  if(_pid == 0) {
    try {
      ::close(0);
      sk::util::Holder<sk::io::InputStream> stdinHolder(sk::util::covariant<sk::io::InputStream>(inputStream.clone()));
      inputStream.close();

      Configurator configurator(_scope);
      _listener.processConfiguring(configurator);
      configurator.finalize();

      _listener.processStarting();
      _scope.notice("start") << cmdline.inspect();

      if(cmdline.empty() == false) {
        std::vector<char*> arguments;
        cmdline.forEach(ExecArgumentCollector(arguments));
        arguments.push_back(0);

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
      throw sk::rt::SystemException("waitpid:" + sk::util::String::valueOf(_pid));
    }
    if(result == _pid) {
      _status = status;
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
  return WIFEXITED(_status) ? true : false;
}

bool
sk::sys::Process::
isKilled() const
{
  ensureNotRunning();
  return WIFSIGNALED(_status) ? true : false;
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
  return WEXITSTATUS(_status);
}

int
sk::sys::Process::
signal() const
{
  if(isKilled() == false) {
    throw sk::util::IllegalStateException("Process exited, not killed");
  }
  return WTERMSIG(_status);
}

bool
sk::sys::Process::
isAlive() const
{
  return _running == true && ::kill(_pid, 0) == 0;
}


/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/SystemException.h>

#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/io/Pipe.h>
#include <sk/io/FileInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

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
    void setEnvironment(const sk::util::String& name, const sk::util::String& value) {
      sk::util::String entry = name.trim() + "=" + value;
      char* s = new char[entry.length() + 1];
      ::strcpy(s, entry.getChars());
      ::putenv(s);
    }
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
      sk::util::Holder<sk::io::InputStream> stdinHolder(inputStream.clone());
      inputStream.close();

      _listener.processStarting();

      Configurator configurator;
      _listener.processConfiguring(configurator);
      
      if(cmdline.empty() == false) {
        std::vector<char*> arguments;
        cmdline.forEach(ExecArgumentCollector(arguments));
        arguments.push_back(0);

        ::execvp(arguments[0], &arguments[0]);
        throw sk::rt::SystemException("exec");
      }
    }
    catch(const std::exception& exception) {
      _scope.error("fork") << exception.what() << ":" << cmdline.inspect();
    }
    _exit(1);
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

void
sk::sys::Process::
stop() 
{
  if(_running == false) {
    return;
  }
  if(signalUnlessTerminates(_listener.processStopping(), SIGTERM)) {
    signalUnlessTerminates(1, SIGKILL);
    try {
      join();
    }
    catch(const std::exception& exception) {}
  }
  _running = false;
}

bool
sk::sys::Process::
signalUnlessTerminates(int timeout, int signal)
{
  if(timeout > 0) {
    time_t start_time = time(0);
    while(true) {
      int status = ::waitpid(_pid, &_status, WNOHANG);
      if(status > 0) {
        return false;
      }
      if(status < 0) {
        if(errno == EINTR) {
          continue;
        }
        throw sk::rt::SystemException("waitpid");
      }
      if(time(0) > (start_time + timeout)) {
        break;
      }
    }
  }
  if(::kill(_pid, signal) != 0 && errno != ESRCH) {
    throw sk::rt::SystemException("kill:" + sk::util::String::valueOf(_pid) + ":" + sk::util::String::valueOf(signal));
  }
  return true;
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
  if(_running == false) {
    return;
  }
  _listener.processJoining();

  while(true) {
    int result = ::waitpid(_pid, &_status, 0);
    if(result < 0) {
      if(errno == EINTR) {
        continue;
      }
      throw sk::rt::SystemException("waitpid");
    }
    if(result == _pid) {
      break;
    }
    throw sk::util::IllegalStateException(
      "waitpid() returned " + sk::util::String::valueOf(result) + ", expected pid " + sk::util::String::valueOf(_pid)
    );
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


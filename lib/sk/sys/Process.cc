/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/SystemException.h>
#include <sk/util/IllegalStateException.h>

#include <sk/sys/Process.h>
#include <sk/io/Pipe.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <sys/time.h>

sk::sys::Process::
Process(sk::io::FileDescriptorInputStream& inputStream, const sk::util::StringArray& cmdline, ProcessListener& listener)
  : _inputStreamHolder(inputStream), _listener(listener)
{
  start(cmdline);
}

sk::sys::Process::
Process(sk::io::FileDescriptorInputStream& inputStream, const sk::util::StringArray& cmdline)
  : _inputStreamHolder(inputStream), _listener(*this)
{
  start(cmdline);
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline, ProcessListener& listener)
  : _listener(listener)
{
  start(cmdline);
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline)
  : _listener(*this)
{
  start(cmdline);
}

sk::sys::Process::
~Process()
{
  try {
    stop();
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR:sk::sys::Process::~Process():" << sk::util::Integer::toString(getpid()) << ": " << exception.what() << std::endl;
    throw;
  }
}

const sk::util::Class
sk::sys::Process::
getClass() const
{
  return sk::util::Class("sk::sys::Process");
}

void
sk::sys::Process::
redirect(int from, const sk::io::FileDescriptor& to)
{
  int fd = to.getFileNumber();
  ::close(from);
  ::dup(fd);
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

void
sk::sys::Process::
start(const sk::util::StringArray& cmdline)
{
  _pid = fork();

  if(_pid < 0) {
    throw sk::util::SystemException("fork()");
  }
  if(_pid == 0) {
    try {
      _listener.processStarting();
      
      processChild(cmdline);
      std::cerr << "ERROR:exec:" << sk::util::Integer::toString(errno) << ":" << strerror(errno) << ":" << cmdline.inspect() << std::endl;
    }
    catch(const std::exception& exception) {
      std::cerr << "ERROR:fork:" << exception.what() << ":" << cmdline.inspect() << std::endl;
    }

    _exit(1);
  }
  if(_inputStreamHolder.isEmpty() == false) {
    _inputStreamHolder.get().close();
  }
}

void
sk::sys::Process::
processChild(const sk::util::StringArray& cmdline)
{
  if(_inputStreamHolder.isEmpty() == false) {
    redirect(0, _inputStreamHolder.get().getFileDescriptor());
    _inputStreamHolder.get().close();
  }
  std::vector<char*> arguments;
  cmdline.forEach(ExecArgumentCollector(arguments));
  arguments.push_back(0);

  ::execvp(arguments[0], &arguments[0]);
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
  if(isAlive() == false) {
    return;
  }
  if(signalUnlessTerminates(_listener.processStopping(), SIGTERM)) {
    signalUnlessTerminates(1, SIGKILL);
    try {
      join();
    }
    catch(const std::exception& exception) {}
  }
  _pid = -1;
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
        throw sk::util::SystemException("waitpid()");
      }
      if(time(0) > (start_time + timeout)) {
        break;
      }
    }
  }
  ::kill(_pid, signal);
  return true;
}

void
sk::sys::Process::
processJoining() 
{
  /*
  sk::io::DataInputStream stream(_ownStreamProviderHolder.get().getStderr().inputStream());
  try {
    while(true) {
      _errors << stream.readLine();
    }
  }
  catch(const sk::io::EOFException& exception) {}
  */
}

void
sk::sys::Process::
join()
{
  if(isAlive() == false) {
    return;
  }
  _listener.processJoining();

  if(::waitpid(_pid, &_status, 0) < 0) {
    throw sk::util::SystemException("waitpid()");
  }
  _pid = -1;
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
  assertNotAlive();

  return WIFEXITED(_status) ? true : false;
}

bool
sk::sys::Process::
isKilled() const
{
  assertNotAlive();

  return WIFSIGNALED(_status) ? true : false;
}

void
sk::sys::Process::
assertNotAlive() const
{
  if(isAlive() == true) {
    throw sk::util::IllegalStateException("Process " + sk::util::Integer::toString(_pid) + " still alive");
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
  return _pid != -1;
}


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
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>

#include "SystemStreamProvider.h"

sk::sys::Process::
Process(const sk::sys::StandardStreamProvider& streamProvider, const sk::util::StringArray& cmdline)
  : _streamProviderHolder(streamProvider), _ownStreamProviderHolder(new sk::sys::SystemStreamProvider)
{
  start(cmdline);
}

sk::sys::Process::
Process(const sk::util::StringArray& cmdline)
  : _ownStreamProviderHolder(new sk::sys::SystemStreamProvider)
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
    // std::cerr << "ERROR:sk::sys::Process::~Process():" << sk::util::Integer::toString(getpid()) << ": " << exception.what() << std::endl;
    // throw;
  }
}

const sk::util::Class
sk::sys::Process::
getClass() const
{
  return sk::util::Class("sk::sys::Process");
}

sk::io::Pipe&
sk::sys::Process::
getStdin() const 
{
  return _ownStreamProviderHolder.get().getStdin();
}

sk::io::Pipe&
sk::sys::Process::
getStdout() const
{
  return _ownStreamProviderHolder.get().getStdout();
}

sk::io::Pipe&
sk::sys::Process::
getStderr() const
{
  return _ownStreamProviderHolder.get().getStderr();
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
      processChild(cmdline);
      std::cerr << "ERROR:exec:" << sk::util::Integer::toString(errno) << ":" << strerror(errno) << ":" << cmdline.inspect() << std::endl;
    }
    catch(const std::exception& exception) {
      std::cerr << "ERROR:fork:" << exception.what() << ":" << cmdline.inspect() << std::endl;
    }

    _exit(1);
  }
  if(_streamProviderHolder.isEmpty() == false) {
    _streamProviderHolder.get().getStdout().closeInput();
  }
  const sk::sys::StandardStreamProvider& provider = _ownStreamProviderHolder.get();

  // provider.getStdin().closeInput();
  // provider.getStdout().closeOutput();
  // provider.getStderr().closeOutput();
}

void
sk::sys::Process::
processChild(const sk::util::StringArray& cmdline)
{
  if(_streamProviderHolder.isEmpty() == false) {
    const sk::sys::StandardStreamProvider& provider = _streamProviderHolder.get();

    redirect(0, provider.getStdout().inputStream().getFileDescriptor());

    provider.getStdin().close();
    provider.getStdout().close();
    provider.getStderr().close();
  }
  const sk::sys::StandardStreamProvider& provider = _ownStreamProviderHolder.get();

  redirect(1, provider.getStdout().outputStream().getFileDescriptor());
  redirect(2, provider.getStderr().outputStream().getFileDescriptor());

  provider.getStdin().close();
  provider.getStdout().close();
  provider.getStderr().close();

  std::vector<char*> arguments;
  cmdline.forEach(ExecArgumentCollector(arguments));
  arguments.push_back(0);

  ::execvp(arguments[0], &arguments[0]);
}

void
sk::sys::Process::
stop() 
{
  if(isAlive() == false) {
    return;
  }
  _ownStreamProviderHolder.get().getStdin().close();

  if(signalUnlessTerminates(1, SIGTERM)) {
    signalUnlessTerminates(1, SIGKILL);
    join();
  }
  _pid = -1;
}

bool
sk::sys::Process::
signalUnlessTerminates(int timeout, int signal)
{
  void (*old_alarm_handler)(int) = ::signal(SIGALRM, SIG_IGN);
  int old_alarm_remainder = ::alarm(timeout);

  int status = ::waitpid(_pid, &_status, 0);
  ::signal(SIGALRM, old_alarm_handler);
  ::alarm(old_alarm_remainder);

  if(status < 0) {
    ::kill(_pid, signal);
    return true;
  }
  return false;
}

void
sk::sys::Process::
join()
{
  if(isAlive() == false) {
    return;
  }
  sk::io::DataInputStream stream(_ownStreamProviderHolder.get().getStderr().inputStream());
  try {
    while(true) {
      _errors << stream.readLine();
    }
  }
  catch(const sk::io::EOFException& exception) {}

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


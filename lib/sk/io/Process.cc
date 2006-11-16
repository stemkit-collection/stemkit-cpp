/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Holder.cxx>
#include <sk/util/SystemException.h>
#include <sk/util/IllegalStateException.h>

#include <sk/io/Process.h>
#include <sk/io/Pipe.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "SystemStreamProvider.h"

sk::io::Process::
Process(const sk::io::StandardStreamProvider& streamProvider, const sk::util::StringArray& cmdline)
  : _streamProviderHolder(streamProvider), _ownStreamProviderHolder(new sk::io::SystemStreamProvider)
{
  start(cmdline);
}

sk::io::Process::
Process(const sk::util::StringArray& cmdline)
  : _ownStreamProviderHolder(new sk::io::SystemStreamProvider)
{
  start(cmdline);
}

sk::io::Process::
~Process()
{
  stop();
}

const sk::util::Class
sk::io::Process::
getClass() const
{
  return sk::util::Class("sk::io::Process");
}

sk::io::Pipe&
sk::io::Process::
getStdin() const 
{
  return _ownStreamProviderHolder.get().getStdin();
}

sk::io::Pipe&
sk::io::Process::
getStdout() const
{
  return _ownStreamProviderHolder.get().getStdout();
}

sk::io::Pipe&
sk::io::Process::
getStderr() const
{
  return _ownStreamProviderHolder.get().getStderr();
}

void 
sk::io::Process::
exec(const sk::util::String& command, const std::vector<char*>& args)
{
  ::execvp(command.getChars(), &args[0]);
}

void
sk::io::Process::
start(const sk::util::StringArray& cmdline)
{
  _pid = fork();
  if(_pid < 0) {
    sk::util::SystemException("fork()");
  }
  if(_pid == 0) {
    ::close(0);
    ::close(1);
    ::close(2);

    _stdin.cloneReadDescriptor();
    _stdout.cloneWriteDescriptor();
    _stderr.cloneWriteDescriptor();

    _stdin.close();
    _stdout.close();
    _stderr.close();

    std::vector<char*> arguments;

    std::for_each(argv.begin(), argv.end(), ExecArgumentPusher(arguments));
    arguments.push_back(0);

    _listener.exec(argv[0], arguments);
    std::cerr << "Process exec failure" << std::endl;
    _exit(1);
  }
  _stdin.closeReadDescriptor();
  _stdout.closeWriteDescriptor();
  _stderr.closeWriteDescriptor();
}

void
sk::io::Process::
stop() 
{
  if(isAlive() == false) {
    return;
  }
  _stdin.close();

  void (*old_alarm_handler)(int) = signal(SIGALRM, SIG_IGN);
  int old_alarm_remainder = alarm(1);

  int status = waitpid(_pid, 0, 0);
  signal(SIGALRM, old_alarm_handler);
  alarm(old_alarm_remainder);

  if(status < 0) {
    kill(_pid, SIGKILL);
  }
  _pid = -1;
}

void
sk::io::Process::
join()
{
  if(isAlive() == false) {
    return;
  }
  _errors = io::StreamContent(_stderr.inputStream()).get();

  if(waitpid(_pid, &_status, 0) < 0) {
    throw sk::util::SystemException("waitpid()");
  }
  _pid = -1;
}

bool
sk::io::Process::
isSuccess() const
{
  return isExited() && exitStatus() == 0;
}

bool
sk::io::Process::
isExited() const
{
  if(isAlive() == true) {
    throw sk::util::IllegalStateException("Process still alive");
  }
  return WIFEXITED(_status) ? true : false;
}

int
sk::io::Process::
exitStatus() const
{
  if(isExited() == false) {
    throw sk::util::IllegalStateException("Process is terminated, not exited");
  }
  return WEXITSTATUS(_status);
}

bool
sk::io::Process::
isAlive() const
{
  return _pid != -1;
}


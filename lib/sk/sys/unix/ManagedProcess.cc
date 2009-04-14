/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/rt/SystemException.h>

#include "ManagedProcess.h"
#include <unistd.h>
#include <signal.h>

static const char* __className("sk::sys::ManagedProcess");

sk::sys::ManagedProcess::
ManagedProcess(pid_t pid)
  : _pid(pid)
{
}

sk::sys::ManagedProcess::
~ManagedProcess()
{
}

const sk::util::Class
sk::sys::ManagedProcess::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::sys::ManagedProcess::
getPid() const
{
  return _pid;
}

void 
sk::sys::ManagedProcess::
stop()
{
  if(terminate(SIGTERM) == false) {
    if(terminate(SIGKILL) == false) {
      throw sk::rt::SystemException("Cannot stop process:" + sk::util::String::valueOf(_pid));
    }
  }
}

bool
sk::sys::ManagedProcess::
terminate(int signal)
{
  if(::kill(_pid, signal) != 0) {
    throw sk::rt::SystemException("kill:" + sk::util::String::valueOf(_pid) + ":" + sk::util::String::valueOf(signal));
  }
  sleep(1);
  return isAlive() == false;
}

void 
sk::sys::ManagedProcess::
join()
{
  while(isAlive() == true) {
    sleep(3);
  }
}

void 
sk::sys::ManagedProcess::
detach()
{
}

bool 
sk::sys::ManagedProcess::
isSuccess() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::sys::ManagedProcess::
isExited() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::sys::ManagedProcess::
isKilled() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::sys::ManagedProcess::
isAlive() const
{
  return ::kill(_pid, 0) == 0;
}

int 
sk::sys::ManagedProcess::
exitStatus() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::sys::ManagedProcess::
signal() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

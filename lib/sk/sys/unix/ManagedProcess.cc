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

#include "ManagedProcess.h"

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

void 
sk::sys::ManagedProcess::
stop()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::ManagedProcess::
join()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::ManagedProcess::
detach()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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

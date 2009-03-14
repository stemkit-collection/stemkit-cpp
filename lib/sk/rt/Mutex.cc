/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/Mutex.h>
#include "thread/Implementation.h"

static const char* __className("sk::rt::Mutex");

sk::rt::Mutex::
Mutex(bool ownership)
  : thread::AbstractLock(thread::Implementation::instance().makeSimpleMutex(), ownership)
{
}

sk::rt::Mutex::
~Mutex()
{
}

const sk::util::Class
sk::rt::Mutex::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::Mutex::
isLocked() const
{
  return tryLockCheck();
}

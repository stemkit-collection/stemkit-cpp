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

#include <sk/rt/thread/Mutex.h>
#include "Implementation.h"

static const sk::util::Class __class("sk::rt::thread::Mutex");

sk::rt::thread::Mutex::
Mutex(bool ownership)
  : AbstractLock(Implementation::instance().makeSimpleMutex(), ownership)
{
}

sk::rt::thread::Mutex::
~Mutex()
{
}

const sk::util::Class
sk::rt::thread::Mutex::
getClass() const
{
  return __class;
}

bool
sk::rt::thread::Mutex::
isLocked() const
{
  return tryLockCheck();
}

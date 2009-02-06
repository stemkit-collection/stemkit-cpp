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
#include <sk/util/Method.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/thread/Mutex.h>

sk::rt::thread::Mutex::
Mutex()
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
  return sk::util::Class("sk::rt::thread::Mutex");
}

void
sk::rt::thread::Mutex::
lock()
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("lock").getName());
}

void
sk::rt::thread::Mutex::
unlock()
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("unlock").getName());
}

void
sk::rt::thread::Mutex::
synchronize(sk::rt::Runnable& block)
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("synchronize").getName());
}

bool
sk::rt::thread::Mutex::
isLocked() const
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("isLocked").getName());
}

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
#include <sk/util/UnsupportedOperationException.h>

#include "Mutex.h"
#include "Implementation.h"

static const char* __className("sk::rt::thread::mock::Implementation");

sk::rt::thread::mock::Implementation::
Implementation()
{
}

sk::rt::thread::mock::Implementation::
~Implementation()
{
}

const sk::util::Class
sk::rt::thread::mock::Implementation::
getClass() const
{
  return sk::util::Class(__className);
}

sk::rt::thread::mock::Mutex*
sk::rt::thread::mock::Implementation::
makeSimpleMutex() const
{
  return new mock::Mutex();
}

sk::rt::thread::mock::Mutex*
sk::rt::thread::mock::Implementation::
makeRecursiveMutex() const
{
  return new mock::Mutex();
}

sk::rt::thread::mock::Thread*
sk::rt::thread::mock::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  return new mock::Thread(target);
}

sk::rt::thread::mock::Thread*
sk::rt::thread::mock::Implementation::
wrapCurrentThread(sk::rt::thread::Generic& handle) const
{
  return new mock::Thread();
}

sk::rt::thread::Generic& 
sk::rt::thread::mock::Implementation::
getGeneric() const
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

void
sk::rt::thread::mock::Implementation::
sleep(uint64_t milliseconds) const 
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

void 
sk::rt::thread::mock::Implementation::
yield() const
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

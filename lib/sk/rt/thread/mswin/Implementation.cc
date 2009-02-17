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

#include "Implementation.h"
#include <windows.h>

static const sk::util::Class __class("sk::rt::thread::mswin::Implementation");

sk::rt::thread::mswin::Implementation::
Implementation()
{
}

sk::rt::thread::mswin::Implementation::
~Implementation()
{
}

const sk::util::Class
sk::rt::thread::mswin::Implementation::
getClass() const
{
  return __class;
}

sk::rt::thread::abstract::Mutex* 
sk::rt::thread::mswin::Implementation::
makeSimpleMutex() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Mutex* 
sk::rt::thread::mswin::Implementation::
makeRecursiveMutex() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Thread* 
sk::rt::thread::mswin::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Thread* 
sk::rt::thread::mswin::Implementation::
wrapCurrentThread(sk::rt::thread::Generic& handle) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::Generic& 
sk::rt::thread::mswin::Implementation::
getGeneric() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::mswin::Implementation::
sleep(uint64_t milliseconds) const
{
  Sleep(milliseconds);
}

void
sk::rt::thread::mswin::Implementation::
yield() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

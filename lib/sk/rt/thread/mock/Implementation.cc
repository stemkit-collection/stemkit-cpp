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

#include "Implementation.h"

static sk::util::Class __class("sk::rt::thread::mock::Implementation");

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
  return __class;
}

sk::rt::thread::mock::Mutex*
sk::rt::thread::mock::Implementation::
makeMutex() const
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

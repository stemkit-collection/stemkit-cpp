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

#include "Implementation.h"
#include "Mutex.h"

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
  return sk::util::Class("sk::rt::thread::mock::Implementation");
}

sk::rt::thread::mock::Mutex*
sk::rt::thread::mock::Implementation::
makeMutex() const
{
  return new mock::Mutex();
}

sk::rt::thread::mock::Thread*
sk::rt::thread::mock::Implementation::
makeThread(sk::rt::Runnable& target) const
{
  return new mock::Thread(target);
}

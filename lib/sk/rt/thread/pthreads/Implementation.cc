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

sk::rt::thread::pthreads::Implementation::
Implementation()
{
}

sk::rt::thread::pthreads::Implementation::
~Implementation()
{
}

const sk::util::Class
sk::rt::thread::pthreads::Implementation::
getClass() const
{
  return sk::util::Class("sk::rt::thread::pthreads::Implementation");
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Implementation::
makeMutex() const
{
  return new pthreads::Mutex();
}

sk::rt::thread::pthreads::Thread*
sk::rt::thread::pthreads::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  return new pthreads::Thread(target, handle);
}

sk::rt::thread::pthreads::Thread*
sk::rt::thread::pthreads::Implementation::
wrapCurrentThread(sk::rt::thread::Generic& handle) const
{
  return new pthreads::Thread(handle);
}

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

#include "Thread.h"

static const char* __className("sk::rt::thread::mock::Thread");

sk::rt::thread::mock::Thread::
Thread()
{
}

sk::rt::thread::mock::Thread::
Thread(sk::rt::Runnable& /*target*/)
{
}

sk::rt::thread::mock::Thread::
~Thread()
{
}

const sk::util::Class
sk::rt::thread::mock::Thread::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::thread::mock::Thread::
start(int stackSize = 0)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::mock::Thread::
stop()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::mock::Thread::
interrupt()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::mock::Thread::
join()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::mock::Thread::
detach()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}


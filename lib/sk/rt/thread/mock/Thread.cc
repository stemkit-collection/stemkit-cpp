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

static const sk::util::Class __class("sk::rt::thread::mock::Thread");

sk::rt::thread::mock::Thread::
Thread()
{
}

sk::rt::thread::mock::Thread::
Thread(sk::rt::Runnable& target)
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
  return __class;
}

void 
sk::rt::thread::mock::Thread::
start()
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


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

#include <sk/rt/thread/abstract/Factory.h>
#include "Mutex.h"

static const sk::util::Class __class("sk::rt::thread::mock::Factory");

sk::rt::thread::abstract::Factory::
Factory()
{
}

sk::rt::thread::abstract::Factory::
~Factory()
{
}

const sk::util::Class
sk::rt::thread::abstract::Factory::
getClass() const
{
  return __class;
}

sk::rt::thread::abstract::Mutex* 
sk::rt::thread::abstract::Factory::
makeMutex() const
{
  return new mock::Mutex;
}

sk::rt::thread::abstract::Thread* 
sk::rt::thread::abstract::Factory::
makeThread(sk::rt::Runnable& target) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

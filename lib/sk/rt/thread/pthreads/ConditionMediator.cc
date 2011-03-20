/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
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

#include "ConditionMediator.h"
#include <sk/rt/TimeoutException.h>

static const sk::util::String __className("sk::rt::thread::pthreads::ConditionMediator");

sk::rt::thread::pthreads::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock, int capacity)
  : _lock(lock)
{
}

sk::rt::thread::pthreads::ConditionMediator::
~ConditionMediator()
{
}

const sk::util::Class
sk::rt::thread::pthreads::ConditionMediator::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::thread::pthreads::ConditionMediator::
invoke(const sk::rt::thread::Conditional& block)
{
  throw sk::util::UnsupportedOperationException("invoke");
}

void
sk::rt::thread::pthreads::ConditionMediator::
ensure(bool expression, uint64_t timeout)
{
  ensure(0, expression, timeout);
}

void
sk::rt::thread::pthreads::ConditionMediator::
ensure(int channel, bool expression, uint64_t timeout)
{
  throw sk::util::UnsupportedOperationException("ensure");
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(bool expression)
{
  announce(0, expression);
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(int channel, bool expression)
{
  throw sk::util::UnsupportedOperationException("announce");
}

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
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/util/Holder.cxx>
#include "thread/Implementation.h"

static const sk::util::String __className("sk::rt::thread::ConditionMediator");

sk::rt::thread::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock, int capacity)
  : _mediatorHolder(thread::Implementation::instance().makeConditionMediator(lock, capacity))
{
}

sk::rt::thread::ConditionMediator::
~ConditionMediator()
{
}

const sk::util::Class
sk::rt::thread::ConditionMediator::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::thread::ConditionMediator::
invoke(const sk::rt::thread::Conditional& block)
{
  _mediatorHolder.getMutable().invoke(block);
}


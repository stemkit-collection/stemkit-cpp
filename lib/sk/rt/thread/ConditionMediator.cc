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
  : _mediatorHolder(thread::Implementation::instance().makeConditionMediator(lock, capacity)),
    _blocking(true)
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
setBlocking(bool state)
{
  _blocking = state;
}

bool
sk::rt::thread::ConditionMediator::
isBlocking() const
{
  return _blocking;
}

bool
sk::rt::thread::ConditionMediator::
sync(const sk::rt::thread::Conditional& block)
{
  return _mediatorHolder.getMutable().invoke(_blocking, block);
}

const sk::util::Object&
sk::rt::thread::ConditionMediator::
getObject() const
{
  return _mediatorHolder.get().getObject();
}

sk::util::Object& 
sk::rt::thread::ConditionMediator::
getObject()
{
  return _mediatorHolder.getMutable().getObject();
}

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
#include "generic/ConditionMediator.h"

static const sk::util::String __className("sk::rt::thread::ConditionMediator");

namespace {
  sk::rt::thread::platform::ConditionMediator* makeConditionMediator(const sk::rt::Scope& scope, sk::rt::Lock& lock, int capacity) {
    if(scope.getProperty("generic-condition-mediator", sk::util::Boolean::B_FALSE) == true) {
      return new sk::rt::thread::generic::ConditionMediator(scope, lock, capacity);
    }
    return sk::rt::thread::Implementation::instance().makeConditionMediator(lock, capacity);
  }
}

sk::rt::thread::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock, int capacity)
  : _scope(__className), _mediatorHolder(makeConditionMediator(_scope, lock, capacity)), _blocking(true)
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

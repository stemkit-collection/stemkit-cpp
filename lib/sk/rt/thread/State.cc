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
#include <sk/util/IndexOutOfBoundsException.h>

#include <sk/rt/thread/State.h>

std::vector<sk::rt::thread::State*> sk::rt::thread::State::_states;
static const sk::util::Class __class("sk::rt::thread::State");

#define DEFINE_STATE(state) const sk::rt::thread::State sk::rt::thread::State::SK_T_##state(#state)

DEFINE_STATE(NEW);
DEFINE_STATE(RUNNABLE);
DEFINE_STATE(BLOCKED);
DEFINE_STATE(WAITING);
DEFINE_STATE(TIMED_WAITING);
DEFINE_STATE(TERMINATED);

sk::rt::thread::State::
State(const sk::util::String& name)
  : _name(name), _value(_states.size())
{
}

sk::rt::thread::State::
~State()
{
}

const sk::util::Class
sk::rt::thread::State::
getClass() const
{
  return __class;
}

const sk::util::String&
sk::rt::thread::State::
getName() const
{
  return _name;
}

int 
sk::rt::thread::State::
toInt() const
{
  return _value;
}

bool
sk::rt::thread::State::
operator==(const State& other) const
{
  return _value == other._value;
}

const sk::util::String
sk::rt::thread::State::
toString() const
{
  return getName();
}

const sk::rt::thread::State&
sk::rt::thread::State::
valueOf(const sk::util::String& name)
{
  for(std::vector<State*>::iterator iterator = _states.begin(); iterator != _states.end() ;++iterator) {
    if(name.equalsIgnoreCase((*iterator)->getName())) {
      return *(*iterator);
    }
  }
  throw sk::util::IndexOutOfBoundsException("sk::rt::thread::State#valueOf()");
}

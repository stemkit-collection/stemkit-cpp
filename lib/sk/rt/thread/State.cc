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
DEFINE_STATE(STARTED);
DEFINE_STATE(RUNNING);
DEFINE_STATE(EXITED);
DEFINE_STATE(STOPPED);
DEFINE_STATE(EXCEPTION);

std::ostream& 
sk::rt::thread::operator<<(std::ostream& stream, const State& state) 
{
  stream << state.inspect();
  return stream;
}

sk::rt::thread::State::
State(const sk::util::String& name)
  : _name(name), _value(_states.size())
{
  _states.push_back(this);
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

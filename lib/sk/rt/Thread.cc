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
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/Thread.h>

#include <sstream>
#include <exception>
#include <iostream>

#include "thread/Dispatcher.h"
#include "thread/Implementation.h"
#include "thread/Runner.h"

static const sk::util::Class __class("sk::rt::Thread");

sk::rt::Thread::
Thread()
  : _targetHolder(*this)
{
  init();
}

sk::rt::Thread::
Thread(const sk::util::String& name)
  : _targetHolder(*this), _name(name)
{
  init();
}

sk::rt::Thread::
Thread(sk::rt::Runnable& target)
  : _targetHolder(target)
{
  init();
}

sk::rt::Thread::
Thread(sk::rt::Runnable& target, const sk::util::String& name)
  : _targetHolder(target), _name(name)
{
  init();
}

sk::rt::Thread::
Thread(sk::rt::Runnable* target)
  : _targetHolder(target)
{
  init();
}

sk::rt::Thread::
Thread(sk::rt::Runnable* target, const sk::util::String& name)
  : _targetHolder(target), _name(name)
{
  init();
}

sk::rt::Thread::
~Thread()
{
  try {
    stop();
  }
  catch(const std::exception& exception) {
    std::cerr << "[" << SK_METHOD << "] " << exception.what() << std::endl;
  }
  catch(...) {
    std::cerr << "[" << SK_METHOD << "] UNKNOWN EXCEPTION" << std::endl;
  }
}

void
sk::rt::Thread::
init()
{
  _id = sk::rt::thread::Dispatcher::main().makeSequence();
  _runnerHolder.set(new thread::Runner(_targetHolder.get()));

  if(_name.isEmpty() == true) {
    std::stringstream stream;
    stream << "Thread" << '-' << _id;
    _name = stream.str();
  }
}

void
sk::rt::Thread::
reset()
{
  sk::rt::thread::Dispatcher::reset();
  sk::rt::thread::Implementation::reset();
}

long long
sk::rt::Thread::
getId() const
{
  return _id;
}

const sk::util::Class
sk::rt::Thread::
getClass() const
{
  return __class;
}

void
sk::rt::Thread::
run() const
{
}

void
sk::rt::Thread::
stop()
{
  if(getState() == thread::State::SK_T_NEW) {
    return;
  }
  if(getState() == thread::State::SK_T_TERMINATED) {
    return;
  }
  _runnerHolder.get().getThreadImplementation().stop();
}

void
sk::rt::Thread::
start()
{
  _runnerHolder.get().start(*this);
}

void 
sk::rt::Thread::
join()
{
  _runnerHolder.get().getThreadImplementation().join();
}

void 
sk::rt::Thread::
interrupt()
{
  _runnerHolder.get().getThreadImplementation().interrupt();
}

bool
sk::rt::Thread::
isMain() const
{
  return false;
}

bool
sk::rt::Thread::
isService() const
{
  return false;
}

bool
sk::rt::Thread::
isRegular() const
{
  return true;
}

bool 
sk::rt::Thread::
isAlive() const
{
  return false;
}

bool 
sk::rt::Thread::
isInterrupted() const
{
  return false;
}

const sk::util::String
sk::rt::Thread::
getName() const
{
  return _name;
}

const sk::rt::thread::State&
sk::rt::Thread::
getState() const
{
  return _runnerHolder.get().getState();
}

sk::rt::thread::Generic& 
sk::rt::Thread::
currentThread()
{
  return sk::rt::thread::Dispatcher::main().currentThread();
}

int 
sk::rt::Thread::
activeCount()
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

void 
sk::rt::Thread::
yield()
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

void 
sk::rt::Thread::
pass()
{
  yield();
}


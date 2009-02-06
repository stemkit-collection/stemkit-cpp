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
#include <sk/util/Method.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/Thread.h>
#include <thread/Dispatcher.h>

#include <sstream>
#include <exception>
#include <iostream>

static sk::util::Class klass("sk::rt::Thread");

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
Thread(const sk::rt::Runnable& target)
  : _targetHolder(target)
{
  init();
}

sk::rt::Thread::
Thread(const sk::rt::Runnable& target, const sk::util::String& name)
  : _targetHolder(target), _name(name)
{
  init();
}

sk::rt::Thread::
Thread(const sk::rt::Runnable* target)
  : _targetHolder(target)
{
  init();
}

sk::rt::Thread::
Thread(const sk::rt::Runnable* target, const sk::util::String& name)
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
    std::cerr << "sk::rt::Thread::~Thread(): " << exception.what() << std::endl;
  }
  catch(...) {
    std::cerr << "sk::rt::Thread::~Thread(): UNKNOWN EXCEPTION" << std::endl;
  }
}

void
sk::rt::Thread::
init()
{
  _stateHolder.set(thread::State::SK_T_NEW);
  _id = sk::rt::thread::Dispatcher::main().makeSequence();

  if(_name.isEmpty() == true) {
    std::stringstream stream;
    stream << "Thread" << '-' << _id;
    _name = stream.str();
  }
}

void
sk::rt::Thread::
setup()
{
  sk::rt::thread::Dispatcher::main();
}

void
sk::rt::Thread::
reset()
{
  sk::rt::thread::Dispatcher::cleanup();
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
  return klass;
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
  if(_stateHolder.get() == thread::State::SK_T_NEW) {
    return;
  }
  if(_stateHolder.get() == thread::State::SK_T_TERMINATED) {
    return;
  }
  throw sk::util::UnsupportedOperationException(getClass().getMethod("stop").getName());
}

void
sk::rt::Thread::
start()
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("start").getName());
}

void 
sk::rt::Thread::
join()
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("join").getName());
}

void 
sk::rt::Thread::
interrupt()
{
  throw sk::util::UnsupportedOperationException(getClass().getMethod("interrupt").getName());
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
  return _stateHolder.get();
}

sk::rt::Thread& 
sk::rt::Thread::
currentThread()
{
  throw sk::util::UnsupportedOperationException(klass.getClassMethod("currentThread").getName());
}

int 
sk::rt::Thread::
activeCount()
{
  throw sk::util::UnsupportedOperationException(klass.getClassMethod("activeCount").getName());
}

void 
sk::rt::Thread::
yield()
{
  throw sk::util::UnsupportedOperationException(klass.getClassMethod("yield").getName());
}

void 
sk::rt::Thread::
pass()
{
  yield();
}


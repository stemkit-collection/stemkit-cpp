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
#include <thread/Dispatcher.h>

#include <sstream>
#include <exception>
#include <iostream>

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
  _id = thread::Dispatcher::main().makeSequence();

  if(_name.isEmpty() == true) {
    std::stringstream stream;
    stream << "Thread" << '-' << _id;
    _name = stream.str();
  }
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
  return sk::util::Class("sk::rt::Thread");
}

void
sk::rt::Thread::
run()
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
  throw sk::util::UnsupportedOperationException("sk::rt::Thread#stop()");
}

void
sk::rt::Thread::
start()
{
  throw sk::util::UnsupportedOperationException("sk::rt::Thread#start()");
}

void 
sk::rt::Thread::
join()
{
  throw sk::util::UnsupportedOperationException("sk::rt::Thread#join()");
}

void 
sk::rt::Thread::
interrupt()
{
  throw sk::util::UnsupportedOperationException("sk::rt::Thread#interrupt()");
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
  throw sk::util::UnsupportedOperationException("sk::rt::Thread.currentThread()");
}

int 
sk::rt::Thread::
activeCount()
{
  throw sk::util::UnsupportedOperationException("sk::rt::Thread.activeCount()");
}

void 
sk::rt::Thread::
yield()
{
  throw sk::util::UnsupportedOperationException("sk::rt::Thread.yield()");
}

void 
sk::rt::Thread::
pass()
{
  yield();
}


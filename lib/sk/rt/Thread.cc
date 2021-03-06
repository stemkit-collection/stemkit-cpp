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
#include <sk/util/IllegalStateException.h>

#include <sk/rt/Thread.h>

#include <sstream>
#include <exception>
#include <iostream>

#include "thread/Dispatcher.h"
#include "thread/Implementation.h"
#include "thread/Runner.h"
#include "thread/Inspector.h"

static const char* __className("sk::rt::Thread");

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
  if(isAlive() == true) {
    _runnerHolder.getMutable().getScope().warning(__FUNCTION__) << "still running: " << inspect();
  }
}

void
sk::rt::Thread::
init()
{
  _id = sk::rt::thread::Dispatcher::main().makeSequence();
  _runnerHolder.set(new thread::Runner(_targetHolder.getMutable(), *this));

  if(_name.isEmpty() == true) {
    std::ostringstream stream;
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
  sk::rt::thread::Dispatcher::reset();
  sk::rt::thread::Implementation::reset();
}

bool
sk::rt::Thread::
isReady()
{
  return sk::rt::thread::Dispatcher::isMainAvailable();
}


uint64_t
sk::rt::Thread::
getId() const
{
  return _id;
}

const sk::util::Class
sk::rt::Thread::
getClass() const
{
  return sk::util::Class(__className);
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
  if(getState() == thread::State::SK_T_RUNNING) {
    _runnerHolder.getMutable().stop();
  }
}

void
sk::rt::Thread::
start()
{
  _runnerHolder.getMutable().start(*this);
}

void
sk::rt::Thread::
join()
{
  if(isDetached() == true) {
    throw sk::util::IllegalStateException("join: detached: " + inspect());
  }
  _runnerHolder.get().getThreadImplementation().join();
}

void
sk::rt::Thread::
interrupt()
{
  _runnerHolder.getMutable().interrupt();
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
  const thread::State& state = getState();
  return state == thread::State::SK_T_RUNNING || state == thread::State::SK_T_STARTED;
}

bool
sk::rt::Thread::
isInterrupted() const
{
  return _runnerHolder.getMutable().isInterrupted();
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
  return _runnerHolder.getMutable().getState();
}

sk::rt::thread::Generic&
sk::rt::Thread::
currentThread()
{
  return sk::rt::thread::Dispatcher::main().currentThread();
}

void
sk::rt::Thread::
sleep(uint64_t milliseconds)
{
  sk::rt::thread::Implementation::instance().sleep(milliseconds);
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
  sk::rt::thread::Implementation::instance().yield();
}

void
sk::rt::Thread::
pass()
{
  yield();
}

void
sk::rt::Thread::
setDefaultUncaughtExceptionHandler(thread::UncaughtExceptionHandler& handler)
{
  sk::rt::thread::Dispatcher::main().setUncaughtExceptionHandler(handler);
}

sk::rt::thread::UncaughtExceptionHandler&
sk::rt::Thread::
getDefaultUncaughtExceptionHandler()
{
  return sk::rt::thread::Dispatcher::main().getUncaughtExceptionHandler();
}

bool
sk::rt::Thread::
isException() const
{
  return false;
}

bool
sk::rt::Thread::
isExited() const
{
  return getState() == thread::State::SK_T_EXITED;
}

int
sk::rt::Thread::
exitStatus() const
{
  if(isExited() == false) {
    throw sk::util::IllegalStateException("thread still running");
  }
  return _runnerHolder.get().getExitStatus();
}

void
sk::rt::Thread::
detach()
{
  _runnerHolder.getMutable().detach();
}

bool
sk::rt::Thread::
isDetached() const
{
  return _runnerHolder.getMutable().isDetached();
}

const sk::util::String
sk::rt::Thread::
inspect() const
{
  return thread::Inspector(*this).inspect();
}

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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/Holder.cxx>

#include "Implementation.h"
#include "Dispatcher.h"
#include "Runner.h"

static const char* __className("sk::rt::thread::Runner");

sk::rt::thread::Runner::
Runner(sk::rt::Runnable& target, sk::rt::thread::Generic& thread)
  : _scope(__className), _target(target), _generic(thread), _stateHolder(thread::State::SK_T_NEW), 
    _exitStatus(-1), _interrupted(false), _detached(false), _stateMutex(false)
{
}

sk::rt::thread::Runner::
~Runner()
{
}

const sk::util::Class
sk::rt::thread::Runner::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::rt::thread::State&
sk::rt::thread::Runner::
getState()
{
  return _stateMutex.synchronize<const State&>(_stateHolder, &util::Holder<State>::get);
}

void
sk::rt::thread::Runner::
setState(const thread::State& state)
{
  typedef void (util::Holder<State>::*member_function_t)(const State&);
  member_function_t set = &util::Holder<State>::set;

  _stateMutex.synchronize(_stateHolder, set, state);
}

sk::rt::Scope& 
sk::rt::thread::Runner::
getScope()
{
  return _scope;
}

sk::rt::thread::abstract::Thread&
sk::rt::thread::Runner::
getThreadImplementation() const
{
  if(_threadHolder.isEmpty() == true) {
    throw sk::util::IllegalStateException("thread not started");
  }
  return _threadHolder.getMutable();
}

void
sk::rt::thread::Runner::
start(sk::rt::thread::Generic& handle)
{
  if(_threadHolder.isEmpty() == false) {
    throw sk::util::IllegalStateException("thread already started");
  }
  _threadHolder.set(thread::Implementation::instance().makeThread(*this, handle));

  setState(thread::State::SK_T_STARTED);
  _threadHolder.getMutable().start();
}

void
sk::rt::thread::Runner::
stop()
{
  const thread::State& original = getState();
  setState(thread::State::SK_T_STOPPED);

  try {
    getThreadImplementation().stop();
  }
  catch(...) {
    setState(original);
  }
}

void 
sk::rt::thread::Runner::
detach()
{
  if(_detached == false) {
    getThreadImplementation().detach();
  }
  _detached = true;
}

bool
sk::rt::thread::Runner::
isDetached()
{
  return _detached;
}

void
sk::rt::thread::Runner::
run() 
{
  setState(thread::State::SK_T_RUNNING);
  try {
    _target.run();
    throw thread::Exit(0);
  }
  catch(const thread::Exit& exception) {
    setState(thread::State::SK_T_EXITED);
    _exitStatus = exception.getCode();
  }
  catch(const std::exception& exception) {
    setState(thread::State::SK_T_EXCEPTION);
    Dispatcher::main().getUncaughtExceptionHandler().uncaughtException(_generic, exception);
  }
  catch(...) {
    if(_stateHolder.get() == thread::State::SK_T_STOPPED) {
      throw;
    }
    setState(thread::State::SK_T_EXCEPTION);
    Dispatcher::main().getUncaughtExceptionHandler().uncaughtException(_generic);
  }
}

int
sk::rt::thread::Runner::
getExitStatus() const
{
  return _exitStatus;
}

void
sk::rt::thread::Runner::
interrupt()
{
  _interrupted = true;
}

bool
sk::rt::thread::Runner::
isInterrupted()
{
  bool state = _interrupted;
  _interrupted = false;

  return state;
}

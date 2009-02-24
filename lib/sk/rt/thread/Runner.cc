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

static const sk::util::Class __class("sk::rt::thread::Runner");

sk::rt::thread::Runner::
Runner(sk::rt::Runnable& target, sk::rt::thread::Generic& thread)
  : _scope(__class.getName()), _target(target), _generic(thread), _stateHolder(thread::State::SK_T_NEW), _exitStatus(-1)
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
  return __class;
}

const sk::rt::thread::State&
sk::rt::thread::Runner::
getState() const
{
  return _stateHolder.get();
}

sk::rt::thread::abstract::Thread&
sk::rt::thread::Runner::
getThreadImplementation() const
{
  if(_threadHolder.isEmpty() == true) {
    throw sk::util::IllegalStateException("thread not started");
  }
  return _threadHolder.get();
}

void
sk::rt::thread::Runner::
start(sk::rt::thread::Generic& handle)
{
  _threadHolder.set(thread::Implementation::instance().makeThread(*this, handle));
  _threadHolder.get().start();
}

void
sk::rt::thread::Runner::
stop()
{
  getThreadImplementation().stop();
  _stateHolder.set(thread::State::SK_T_STOPPED);
}

void
sk::rt::thread::Runner::
run() 
{
  _stateHolder.set(thread::State::SK_T_RUNNING);
  try {
    _target.run();
    throw thread::Exit(0);
  }
  catch(const thread::Exit& exception) {
    _stateHolder.set(thread::State::SK_T_EXITED);
    _exitStatus = 0;
  }
  catch(const std::exception& exception) {
    _stateHolder.set(thread::State::SK_T_EXCEPTION);
    Dispatcher::main().getUncaughtExceptionHandler().uncaughtException(_generic, exception);
  }
  catch(...) {
    _stateHolder.set(thread::State::SK_T_EXCEPTION);
    Dispatcher::main().getUncaughtExceptionHandler().uncaughtException(_generic);
  }
}

int
sk::rt::thread::Runner::
getExitStatus() const
{
  return _exitStatus;
}

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
#include <sk/util/Holder.cxx>

#include "Implementation.h"
#include "Runner.h"

static const sk::util::Class __class("sk::rt::thread::Runner");

sk::rt::thread::Runner::
Runner(sk::rt::Runnable& target)
  : _target(target), _stateHolder(thread::State::SK_T_NEW)
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
run() const
{
  _stateHolder.set(thread::State::SK_T_RUNNABLE);
  try {
    _target.run();
  }
  catch(...) {}

  _stateHolder.set(thread::State::SK_T_TERMINATED);
}

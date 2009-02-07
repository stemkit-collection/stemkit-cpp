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

void
sk::rt::thread::Runner::
run() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

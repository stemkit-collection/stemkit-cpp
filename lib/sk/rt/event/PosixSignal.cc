/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/rt/event/PosixSignal.h>

#include <sk/util/Class.h>
#include <signal.h>

namespace {
  const sk::util::String __className("sk::rt::event::PosixSignal");
}

#define DEFINE_SIGNAL(signal) const sk::rt::event::PosixSignal sk::rt::event::PosixSignal::signal(SIG##signal, #signal)

DEFINE_SIGNAL(HUP);
DEFINE_SIGNAL(INT);
DEFINE_SIGNAL(QUIT);
DEFINE_SIGNAL(PIPE);
DEFINE_SIGNAL(CHLD);
DEFINE_SIGNAL(TERM);
DEFINE_SIGNAL(ALRM);
DEFINE_SIGNAL(USR1);
DEFINE_SIGNAL(USR2);

sk::rt::event::PosixSignal::
PosixSignal(int signal, const sk::util::String& name)
  : _signal(signal), _name(name)
{
}

sk::rt::event::PosixSignal::
~PosixSignal()
{
}

const sk::util::Class
sk::rt::event::PosixSignal::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::rt::event::PosixSignal::
toString() const
{
  return "SIG" + _name;
}

const sk::util::String
sk::rt::event::PosixSignal::
inspect() const
{
  return "<" + getClass().getName() + ": " + toString() + "/" + sk::util::String::valueOf(_signal) + ">";
}

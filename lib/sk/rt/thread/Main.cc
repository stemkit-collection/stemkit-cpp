/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>

#include "Main.h"
#include "Implementation.h"
#include "Inspector.h"

static sk::util::Class __class("sk::rt::thread::Main");

sk::rt::thread::Main::
Main()
  : _threadHolder(Implementation::instance().wrapCurrentThread(*this))
{
}

sk::rt::thread::Main::
~Main()
{
}

const sk::util::Class
sk::rt::thread::Main::
getClass() const
{
  return __class;
}

uint64_t
sk::rt::thread::Main::
getId() const
{
  return 0;
}

void 
sk::rt::thread::Main::
start()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::Main::
stop()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::Main::
join()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::Main::
interrupt()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String 
sk::rt::thread::Main::
getName() const
{
  return "Main";
}

const sk::rt::thread::State& 
sk::rt::thread::Main::
getState() const
{
  return State::SK_T_RUNNING;
}

bool 
sk::rt::thread::Main::
isAlive() const
{
  return true;
}

bool
sk::rt::thread::Main::
isMain() const
{
  return true;
}

bool
sk::rt::thread::Main::
isService() const
{
  return false;
}

bool
sk::rt::thread::Main::
isRegular() const
{
  return false;
}

bool 
sk::rt::thread::Main::
isInterrupted() const
{
  return false;
}

bool 
sk::rt::thread::Main::
isException() const
{
  return false;
}

bool 
sk::rt::thread::Main::
isExited() const
{
  return false;
}

int 
sk::rt::thread::Main::
exitStatus() const
{
  throw sk::util::IllegalStateException(SK_METHOD);
}

void
sk::rt::thread::Main::
detach()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::rt::thread::Main::
isDetached() const
{
  return false;
}

const sk::util::String
sk::rt::thread::Main::
inspect() const
{
  return Inspector(*this).inspect();
}

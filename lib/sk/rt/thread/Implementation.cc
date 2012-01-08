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

#include <sk/rt/thread/platform/Factory.h>
#include "Implementation.h"

sk::rt::thread::platform::Implementation* sk::rt::thread::Implementation::_implementation = 0;

sk::rt::thread::Implementation::
Implementation()
{
}

sk::rt::thread::Implementation::
~Implementation()
{
}

const sk::util::Class
sk::rt::thread::Implementation::
getClass() const
{
  return sk::util::Class("sk::rt::thread::Implementation");
}

sk::rt::thread::platform::Implementation&
sk::rt::thread::Implementation::
instance()
{
  if(_implementation == 0) {
    _implementation = platform::Factory().makeImplementation();
  }
  return *_implementation;
}

void
sk::rt::thread::Implementation::
reset()
{
  if(_implementation != 0) {
    delete _implementation;
    _implementation = 0;
  }
}

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

#include <sk/rt/thread/abstract/Factory.h>
#include "Implementation.h"

sk::util::Holder<sk::rt::thread::abstract::Implementation> sk::rt::thread::Implementation::_implementationHolder;

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

sk::rt::thread::abstract::Implementation&
sk::rt::thread::Implementation::
instance() 
{
  if(_implementationHolder.isEmpty() == true) {
    _implementationHolder.set(abstract::Factory().makeImplementation());
  }
  return _implementationHolder.get();
}

void
sk::rt::thread::Implementation::
reset()
{
  _implementationHolder.clear();
}

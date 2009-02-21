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

#include <sk/rt/thread/abstract/Factory.h>
#include "Implementation.h"

static const sk::util::Class __class("sk::rt::thread::abstract::Factory");

const sk::util::Class
sk::rt::thread::abstract::Factory::
getClass() const
{
  return __class;
}

sk::rt::thread::abstract::Implementation* 
sk::rt::thread::abstract::Factory::
makeImplementation() const
{
  return new win32::Implementation;
}

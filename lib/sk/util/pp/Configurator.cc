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

#include "Configurator.h"

static const sk::util::String __className("sk::util::pp::Configurator");

sk::util::pp::Configurator::
Configurator()
  : _compact(true)
{
}

sk::util::pp::Configurator::
~Configurator()
{
}

const sk::util::Class
sk::util::pp::Configurator::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::util::pp::Configurator::
setCompact(bool state) 
{
  _compact = state;
}

bool
sk::util::pp::Configurator::
isCompact() const
{
  return _compact;
}

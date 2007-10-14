/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IllegalStateException.h>

#include "DisablingConfig.h"

sk::rt::logger::DisablingConfig::
DisablingConfig()
{
}

sk::rt::logger::DisablingConfig::
~DisablingConfig()
{
}

const sk::util::Class
sk::rt::logger::DisablingConfig::
getClass() const
{
  return sk::util::Class("sk::rt::logger::DisablingConfig");
}

bool
sk::rt::logger::DisablingConfig::
checkLevel(const sk::rt::logger::Level& level) const
{
  return false;
}

std::ostream&
sk::rt::logger::DisablingConfig::
stream() const
{
  throw sk::util::IllegalStateException("stream()");
}

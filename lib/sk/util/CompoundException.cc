/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/util/CompoundException.h>

static const sk::util::String __className("sk::util::CompoundException");

sk::util::CompoundException::
CompoundException(const sk::util::List<sk::util::Exception>& exceptions)
  : sk::util::Exception(sk::util::Strings("Compound") << sk::util::String::valueOf(exceptions.size()))
{
}

const sk::util::Class
sk::util::CompoundException::
getClass() const
{
  return sk::util::Class(__className);
}

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
#include <sk/util/Strings.h>

#include <sk/util/ClassCastException.h>

static const char* __className("sk::util::ClassCastException");

sk::util::ClassCastException::
ClassCastException(const sk::util::String& sourceName)
  : Exception(sk::util::Strings("Illegal cast") << sourceName), _sourceName(sourceName)
{
}

sk::util::ClassCastException::
~ClassCastException() throw()
{
}

const sk::util::Class
sk::util::ClassCastException::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::ClassCastException::
sourceName() const
{
  return _sourceName;
}

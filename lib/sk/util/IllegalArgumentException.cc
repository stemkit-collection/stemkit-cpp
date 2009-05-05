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

#include <sk/util/IllegalArgumentException.h>

static const char* __className("sk::util::IllegalArgumentException");

sk::util::IllegalArgumentException::
IllegalArgumentException(const sk::util::String& message)
  : sk::util::Exception(join("Illegal argument", message))
{
}

const sk::util::Class
sk::util::IllegalArgumentException::
getClass() const
{
  return sk::util::Class(__className);
}
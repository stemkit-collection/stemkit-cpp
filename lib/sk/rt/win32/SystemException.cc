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

#include <sk/rt/SystemException.h>

static const char* __className("sk::rt::SystemException");

sk::rt::SystemException::
SystemException()
{
}

sk::rt::SystemException::
~SystemException()
{
}

const sk::util::Class
sk::rt::SystemException::
getClass() const
{
  return sk::util::Class(__className);
}

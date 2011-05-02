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
#include <sk/util/String.h>

#include <sk/net/ConnectException.h>

static const sk::util::String __className("sk::net::ConnectException");

sk::net::ConnectException::
ConnectException()
{
}

sk::net::ConnectException::
~ConnectException()
{
}

const sk::util::Class
sk::net::ConnectException::
getClass() const
{
  return sk::util::Class(__className);
}

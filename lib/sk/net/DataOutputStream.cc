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

#include <sk/net/DataOutputStream.h>

static const sk::util::String __className("sk::net::DataOutputStream");

sk::net::DataOutputStream::
DataOutputStream(sk::io::OutputStream& stream)
  : sk::io::DataOutputStream(stream)
{
}

sk::net::DataOutputStream::
~DataOutputStream()
{
}

const sk::util::Class
sk::net::DataOutputStream::
getClass() const
{
  return sk::util::Class(__className);
}

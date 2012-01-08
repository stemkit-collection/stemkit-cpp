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

#include <sk/io/NullDevice.h>

static const char* __className("sk::io::NullDevice");

sk::io::NullDevice::
NullDevice()
  : sk::io::File("/dev/null", "r+")
{
}

sk::io::NullDevice::
~NullDevice()
{
}

const sk::util::Class
sk::io::NullDevice::
getClass() const
{
  return sk::util::Class(__className);
}

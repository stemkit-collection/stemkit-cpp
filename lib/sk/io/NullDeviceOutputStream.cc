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

#include <sk/io/NullDeviceOutputStream.h>

static const char* __className("sk::io::NullDeviceOutputStream");

sk::io::NullDeviceOutputStream::
NullDeviceOutputStream()
  : FileOutputStream("/dev/null")
{
}

sk::io::NullDeviceOutputStream::
~NullDeviceOutputStream()
{
}

const sk::util::Class
sk::io::NullDeviceOutputStream::
getClass() const
{
  return sk::util::Class(__className);
}

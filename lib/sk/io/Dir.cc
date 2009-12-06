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
#include <sk/util/String.h>

#include <sk/io/Dir.h>

static const sk::util::String __className("sk::io::Dir");

sk::io::Dir::
Dir()
{
}

sk::io::Dir::
~Dir()
{
}

const sk::util::Class
sk::io::Dir::
getClass() const
{
  return sk::util::Class(__className);
}

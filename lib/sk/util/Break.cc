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

#include <sk/util/Break.h>

static const sk::util::String __className("sk::util::Break");

sk::util::Break::
Break()
{
}

sk::util::Break::
~Break()
{
}

const sk::util::Class
sk::util::Break::
getClass() const
{
  return sk::util::Class(__className);
}

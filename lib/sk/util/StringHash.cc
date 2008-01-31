/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/StringHash.h>

sk::util::StringHash::
StringHash()
{
}

sk::util::StringHash::
~StringHash()
{
}

const sk::util::Class
sk::util::StringHash::
getClass() const
{
  return sk::util::Class("sk::util::StringHash");
}

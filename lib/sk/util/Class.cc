/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

sk::util::Class::
Class(const sk::util::String& string)
{
}

sk::util::Class::
~Class()
{
}

const sk::util::Class
sk::util::Class::
getClass() const
{
  return sk::util::Class("sk::util::Class");
}

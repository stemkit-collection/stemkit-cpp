/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/AbstractList.h>

sk::util::AbstractList::
AbstractList()
{
}

sk::util::AbstractList::
~AbstractList()
{
}

const sk::util::Class
sk::util::AbstractList::
getClass() const
{
  return sk::util::Class("sk::util::AbstractList");
}

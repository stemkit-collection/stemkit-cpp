/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/Pathname.h>

sk::util::Pathname::
Pathname(const sk::util::String& component)
  : _collector(component)
{
}

sk::util::Pathname::
~Pathname()
{
}

const sk::util::Class
sk::util::Pathname::
getClass() const
{
  return sk::util::Class("sk::util::Pathname");
}

sk::util::Pathname&
sk::util::Pathname::
front(const sk::util::String& component)
{
  return *this;
}

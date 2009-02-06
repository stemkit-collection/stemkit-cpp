/*  vim: set sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>

sk::util::Class::
Class(const sk::util::String& name)
  : _name(name)
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

const sk::util::String
sk::util::Class::
getName() const
{
  return _name;
}

const sk::util::Method
sk::util::Class::
getMethod(const sk::util::String& name) const
{
  return sk::util::Method(name, *this, true);
}

const sk::util::Method
sk::util::Class::
getClassMethod(const sk::util::String& name) const
{
  return sk::util::Method(name, *this, false);
}

const sk::util::String 
sk::util::Class::
toString() const
{
  return getClass().getName() + "<" + _name + ">#" + sk::util::Integer::toString(getId());
}

const sk::util::String 
sk::util::Class::
inspect() const
{
  return toString();
}

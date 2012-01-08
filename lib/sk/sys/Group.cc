/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/Group.h>

sk::sys::Group::
Group(const sk::util::String& name, int id)
  : _name(name), _id(id)
{
}

sk::sys::Group::
~Group()
{
}

const sk::util::Class
sk::sys::Group::
getClass() const
{
  return sk::util::Class("sk::sys::Group");
}

const sk::util::String
sk::sys::Group::
getName() const
{
  return _name;
}

int
sk::sys::Group::
getGid() const
{
  return _id;
}

const sk::sys::Group
sk::sys::Group::
find(const sk::util::String& name)
{
  return sk::sys::Group(name, 0);
}

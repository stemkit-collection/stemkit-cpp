/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/User.h>

sk::sys::User::
User(const sk::util::String& name, int id)
  : _name(name), _id(id)
{
}

sk::sys::User::
~User()
{
}

const sk::util::Class
sk::sys::User::
getClass() const
{
  return sk::util::Class("sk::sys::User");
}

const sk::util::String
sk::sys::User::
getName() const
{
  return _name;
}

int
sk::sys::User::
getUid() const
{
  return _id;
}

const sk::sys::User
sk::sys::User::
find(const sk::util::String& name)
{
  return sk::sys::User(name, 0);
}

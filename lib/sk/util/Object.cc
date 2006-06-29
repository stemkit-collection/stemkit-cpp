/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Object.h>
#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>

sk::util::Object::
Object() 
{
}

sk::util::Object::
~Object()
{
}

sk::util::Object&
sk::util::Object::
self()
{
  return *this;
}

const sk::util::Object&
sk::util::Object::
self() const
{
  return *this;
}

const sk::util::Class
sk::util::Object::
getClass() const
{
  return Class("sk::util::Object");
}

long long
sk::util::Object::
getId() const
{
  return reinterpret_cast<long long>(this);
}

const sk::util::String
sk::util::Object::
toString() const
{
  return getClass().getName() + "#" + Integer::toString(getId());
}

const sk::util::String 
sk::util::Object::
inspect() const
{
  return toString();
}

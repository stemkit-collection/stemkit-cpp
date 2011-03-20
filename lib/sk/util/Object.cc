/*  vi: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Object.h>
#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sstream>

sk::util::Object::
Object() 
{
}

sk::util::Object::
~Object()
{
}

sk::util::Object*
sk::util::Object::
clone() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::Class
sk::util::Object::
getClass() const
{
  return Class("sk::util::Object");
}

uint64_t
sk::util::Object::
getId() const
{
  uint64_t id = (0U + (reinterpret_cast<const char*>(this) - reinterpret_cast<const char*>(0U)));
  return id;
}

const sk::util::String
sk::util::Object::
toString() const
{
  std::stringstream stream;
  stream << '<' << getClass().getName() << '#' << std::hex << getId() << '>';

  return stream.str();
}

const sk::util::String 
sk::util::Object::
inspect() const
{
  return toString();
}

sk::util::Object& 
sk::util::Object::
getObject()
{
  return *this;
}

const sk::util::Object& 
sk::util::Object::
getObject() const
{
  return *this;
}

bool 
sk::util::
operator<(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first < &second;
}

bool 
sk::util::
operator>(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first > &second;
}

bool 
sk::util::
operator==(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first == &second;
}

bool 
sk::util::
operator!=(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first != &second;
}

bool 
sk::util::
operator<=(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first <= &second;
}

bool 
sk::util::
operator>=(const sk::util::Object& first, const sk::util::Object& second)
{
  return &first >= &second;
}

std::ostream&
sk::util::
operator<<(std::ostream& stream, const sk::util::Object& object)
{
  return stream << object.inspect();
}

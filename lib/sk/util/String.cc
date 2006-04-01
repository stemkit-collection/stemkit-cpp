/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

sk::util::String::
String()
{
}

sk::util::String::
String(const char* buffer)
  : std::string(buffer)
{
}

sk::util::String::
String(const std::string& string)
  : std::string(string)
{
}

sk::util::String::
~String()
{
}

const sk::util::Class
sk::util::String::
getClass() const
{
  return sk::util::Class("sk::util::String");
}

const sk::util::String 
sk::util::String::
operator + (const char* buffer) const
{
  return operator+(String(buffer));
}

const sk::util::String 
sk::util::String::
operator + (const std::string& string) const
{
  const std::string& self = *this;
  return self + string;
}

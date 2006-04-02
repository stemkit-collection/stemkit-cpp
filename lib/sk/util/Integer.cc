/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>

#include <sstream>
#include <iomanip>

sk::util::Integer::
Integer(int value)
  : _value(value)
{
}

sk::util::Integer::
~Integer()
{
}

const sk::util::Class
sk::util::Integer::
getClass() const
{
  return sk::util::Class("sk::util::Integer");
}

const sk::util::String
sk::util::Integer::
toString(int value)
{
  return toString(value, 10);
}

const sk::util::String
sk::util::Integer::
toString(int value, int radix)
{
  std::stringstream stream;
  stream << std::setbase(radix) << value;

  return stream.str();
}

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IndexOutOfBoundsException.h>

#include <sk/util/StringArray.h>

sk::util::StringArray::
StringArray()
{
}

sk::util::StringArray::
StringArray(const sk::util::String& item)
  : std::vector<sk::util::String>(1, item)
{
}

sk::util::StringArray::
StringArray(const char* item)
  : std::vector<sk::util::String>(1, item)
{
}

sk::util::StringArray::
~StringArray()
{
}

const sk::util::Class
sk::util::StringArray::
getClass() const
{
  return sk::util::Class("sk::util::StringArray");
}

int
sk::util::StringArray::
size() const
{
  return std::vector<sk::util::String>::size();
}

const sk::util::String&
sk::util::StringArray::
get(int index) const
{
  if(index<0 || index>=size()) {
    throw sk::util::IndexOutOfBoundsException("get()");
  }
  return std::vector<sk::util::String>::at(index);
}

sk::util::StringArray
sk::util::StringArray::
operator + (const sk::util::String& item) const
{
  StringArray array(*this);

  array.push_back(item);
  return array;
}

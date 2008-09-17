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

const sk::util::String
sk::util::StringArray::
inspect() const
{
  sk::util::String joined;
  const_iterator iterator = begin();

  while(iterator != end() ) {
    joined += (*iterator).inspect();
    if(++iterator != end()) {
      joined += ',';
    }
    joined += ' ';
  }
  if(joined.size() > 0) {
    joined = " " + joined;
  }
  return getClass().getName() + '[' + joined + ']';
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& separator) const
{
  sk::util::String joined;
  const_iterator iterator = begin();

  while(iterator != end() ) {
    joined += (*iterator);
    if(++iterator != end()) {
      joined += separator;
    }
  }
  return joined;
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

void
sk::util::StringArray::
forEach(const sk::util::Processor<const sk::util::String>& processor) const
{
  for(const_iterator iterator=begin(); iterator != end() ;++iterator) {
    processor.process(*iterator);
  }
}

sk::util::StringArray&
sk::util::StringArray::
operator << (const sk::util::String& item) 
{
  push_back(item);
  return *this;
}

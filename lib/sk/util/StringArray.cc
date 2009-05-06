/*  vi: sw=2: 
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IndexOutOfBoundsException.h>

#include <sk/util/StringArray.h>

static const char* __className = "sk::util::StringArray";

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
  return sk::util::Class(__className);
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

bool
sk::util::StringArray::
isEmpty() const
{
  return empty();
}

sk::util::StringArray
sk::util::StringArray::
operator + (const sk::util::String& item) const
{
  StringArray array(*this);
  return array << item;
}

namespace {
  struct Propagator : public virtual sk::util::Processor<const sk::util::String> {
    Propagator(sk::util::StringArray& destination)
      : _destination(destination) {}

    void process(const sk::util::String& item) const {
      _destination << item;
    }
    sk::util::StringArray& _destination;
  };
}

sk::util::StringArray
sk::util::StringArray::
operator + (const sk::util::StringArray& other) const
{
  StringArray array(*this);
  other.forEach(Propagator(array));
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

const sk::util::StringArray 
sk::util::StringArray::
parse(const sk::util::String& specification)
{
  return parse(specification, " ");
}

const sk::util::StringArray 
sk::util::StringArray::
parse(const sk::util::String& specification, const sk::util::String& separator)
{
  sk::util::StringArray result;
  std::string::size_type head_index = 0;
  while(true) {
    std::string::size_type tail_index = specification.find_first_of(separator, head_index);
    if(tail_index == std::string::npos) {
      result << specification.substr(head_index);
      break;
    } 
    result << specification.substr(head_index, tail_index - head_index);
    head_index = tail_index + 1;
  }
  return result;
}

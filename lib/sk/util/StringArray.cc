/*  vi: sw=2: 
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/StringArray.h>
#include <sk/util/mapper/Inspecting.hxx>
#include <sk/util/ArrayList.cxx>

static const char* __className = "sk::util::StringArray";

sk::util::StringArray::
StringArray()
{
}

sk::util::StringArray::
StringArray(const sk::util::String& item)
{
  add(item);
}

sk::util::StringArray::
StringArray(const char* item)
{
  add(item);
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
  return getClass().getName() + '[' + join(" ", ", ", " ", sk::util::mapper::Inspecting<String>()) + ']';
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& prologue, const sk::util::String& separator) const
{
  return join(prologue, separator, sk::util::String::EMPTY);
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const
{
  if(isEmpty() == true) {
    return sk::util::String::EMPTY;
  }
  return prologue + join(separator) + epilogue;
}

const sk::util::StringArray
sk::util::StringArray::
map(const sk::util::Mapper<const sk::util::String>& mapper) const
{
  sk::util::StringArray result;
  struct Mapper : public virtual sk::util::Processor<const sk::util::String> {
    Mapper(sk::util::StringArray& array, const sk::util::Mapper<const sk::util::String>& mapper)
      : _array(array), _mapper(mapper) {}

    void process(const sk::util::String& item) const {
      _array << _mapper.map(item);
    }
    sk::util::StringArray& _array; 
    const sk::util::Mapper<const sk::util::String>& _mapper;
  };
  forEach(Mapper(result, mapper));

  return result;
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

sk::util::StringArray&
sk::util::StringArray::
operator << (const sk::util::String& item) 
{
  addLast(item);
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
  if(specification.isEmpty() == true) {
    return result;
  }
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

const sk::util::String&
sk::util::StringArray::
first() const
{
  return getFirst();
}

const sk::util::String&
sk::util::StringArray::
last() const
{
  return getLast();
}

const sk::util::String
sk::util::StringArray::
shift()
{
  sk::util::String item = getFirst();
  removeFirst();

  return item;
}

const sk::util::String
sk::util::StringArray::
pop()
{
  sk::util::String item = getLast();
  removeLast();

  return item;
}

const sk::util::StringArray
sk::util::StringArray::
slice(int number) const
{
  sk::util::StringArray result;
  if(number<0 || number>size()) {
    throw sk::util::NoSuchElementException("slice");
  }
  const std::deque<sk::util::String>& self = *this;
  for(int index=0; index<number ;++index) {
    result << self[index];
  }
  return result;
}

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
#include <sk/util/NoSuchElementException.h>

#include <sk/util/StringArray.h>
#include <sk/util/mapper/Inspecting.hxx>

static const char* __className = "sk::util::StringArray";

sk::util::StringArray::
StringArray()
{
}

sk::util::StringArray::
StringArray(const sk::util::String& item)
  : std::deque<sk::util::String>(1, item)
{
}

sk::util::StringArray::
StringArray(const char* item)
  : std::deque<sk::util::String>(1, item)
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
  return getClass().getName() + '[' + map(sk::util::mapper::Inspecting<sk::util::String>()).join(" ", ", ", " ") + ']';
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& separator) const
{
  return join(sk::util::String::EMPTY, separator, sk::util::String::EMPTY);
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
  sk::util::String joined;
  const_iterator iterator = begin();

  while(iterator != end() ) {
    joined += (*iterator);
    if(++iterator != end()) {
      joined += separator;
    }
  }
  return prologue + joined + epilogue;
}

const sk::util::StringArray
sk::util::StringArray::
map(const sk::util::Mapper<const sk::util::String, sk::util::String>& mapper) const
{
  sk::util::StringArray result;
  struct Mapper : public virtual sk::util::Processor<const sk::util::String> {
    Mapper(sk::util::StringArray& array, const sk::util::Mapper<const sk::util::String, sk::util::String>& mapper)
      : _array(array), _mapper(mapper) {}

    void process(const sk::util::String& item) const {
      _array << _mapper.map(item);
    }
    sk::util::StringArray& _array; 
    const sk::util::Mapper<const sk::util::String, sk::util::String>& _mapper;
  };
  forEach(Mapper(result, mapper));

  return result;
}

int
sk::util::StringArray::
size() const
{
  return std::deque<sk::util::String>::size();
}

const sk::util::String&
sk::util::StringArray::
get(int index) const
{
  if(index<0 || index>=size()) {
    throw sk::util::IndexOutOfBoundsException("get()");
  }
  const std::deque<sk::util::String>& self = *this;
  return self[index];
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
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException("first");
  }
  return std::deque<sk::util::String>::front();
}

const sk::util::String&
sk::util::StringArray::
last() const
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException("last");
  }
  return std::deque<sk::util::String>::back();
}

const sk::util::String
sk::util::StringArray::
shift()
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException("shift");
  }
  const sk::util::String item = std::deque<sk::util::String>::front();
  pop_front();

  return item;
}

const sk::util::String
sk::util::StringArray::
pop()
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException("pop");
  }
  const sk::util::String item = std::deque<sk::util::String>::back();
  pop_back();

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

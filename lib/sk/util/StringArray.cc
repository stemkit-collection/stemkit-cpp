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
#include <sk/util/mapper/Coercing.hxx>
#include <sk/util/processor/Slicing.hxx>
#include <sk/util/processor/Copying.hxx>
#include <sk/util/processor/Mapping.hxx>
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
StringArray(const sk::util::StringArray& other)
{
  set(other);
}

sk::util::StringArray::
~StringArray()
{
}

sk::util::StringArray&
sk::util::StringArray::
operator = (const sk::util::StringArray& other)
{
  clear();
  set(other);

  return *this;
}

void
sk::util::StringArray::
set(const sk::util::StringArray& other)
{
  other.forEach(sk::util::processor::Copying<String>(*this));
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
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue, const sk::util::Mapper<const String>& mapper) const
{
  if(isEmpty() == true) {
    return sk::util::String::EMPTY;
  }
  return prologue + join(separator, mapper) + epilogue;
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::Mapper<const String>& mapper) const
{
  return join(prologue, separator, sk::util::String::EMPTY, mapper);
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const
{
  return join(prologue, separator, epilogue, sk::util::mapper::Coercing<const String>());
}

const sk::util::String
sk::util::StringArray::
join(const sk::util::String& prologue, const sk::util::String& separator) const
{
  return join(prologue, separator, sk::util::String::EMPTY);
}

const sk::util::StringArray
sk::util::StringArray::
map(const sk::util::Mapper<const sk::util::String>& mapper) const
{
  sk::util::StringArray result;
  forEach(sk::util::processor::Mapping<const String>(sk::util::processor::Copying<String>(result), mapper));

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
slice(int start, int end) const
{
  sk::util::StringArray result;
  forEach(sk::util::processor::Slicing<const String>(start, end, sk::util::processor::Copying<String>(result)));

  return result;
}

const sk::util::StringArray
sk::util::StringArray::
slice(int end) const
{
  return slice(0, end);
}

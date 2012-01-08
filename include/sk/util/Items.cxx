/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ITEMS_CXX_
#define _SK_UTIL_ITEMS_CXX_

#include <sk/util/Items.hxx>
#include <sk/util/ArrayList.cxx>
#include <sk/util/processor/Copying.hxx>
#include <sk/util/processor/Mapping.hxx>
#include <sk/util/processor/Slicing.hxx>
#include <sk/util/mapper/Inspecting.hxx>
#include <sk/util/mapper/Stringing.hxx>

template<typename T>
sk::util::Items<T>::
Items()
{
}

template<typename T>
sk::util::Items<T>::
Items(const T& item)
{
  add(item);
}

template<typename T>
sk::util::Items<T>::
Items(const sk::util::Items<T>& other)
  : super_t(other)
{
}

template<typename T>
sk::util::Items<T>::
~Items()
{
}

template<typename T>
sk::util::Items<T>&
sk::util::Items<T>::
operator = (const sk::util::Items<T>& other)
{
  super_t& item = *this;
  item = other;

  return *this;
}

template<typename T>
const sk::util::Class
sk::util::Items<T>::
getClass() const
{
  return sk::util::Class("sk::util::Items<>");
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
toString() const
{
  return join();
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
inspect() const
{
  return getClass().getName() + '[' + join(" ", ", ", " ", sk::util::mapper::Inspecting<T>()) + ']';
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue, const sk::util::Mapper<const T, const String>& mapper) const
{
  if(super_t::isEmpty() == true) {
    return sk::util::String::EMPTY;
  }
  return prologue + join(separator, mapper) + epilogue;
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::Mapper<const T, const String>& mapper) const
{
  return join(prologue, separator, sk::util::String::EMPTY, mapper);
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const
{
  return join(prologue, separator, epilogue, sk::util::mapper::Stringing<const T>());
}

template<typename T>
const sk::util::String
sk::util::Items<T>::
join(const sk::util::String& prologue, const sk::util::String& separator) const
{
  return join(prologue, separator, sk::util::String::EMPTY);
}

template<typename T>
const sk::util::Items<T>
sk::util::Items<T>::
map(const sk::util::Mapper<const T>& mapper) const
{
  sk::util::Items<T> result;
  forEach(sk::util::processor::Mapping<const T>(sk::util::processor::Copying<T>(result), mapper));

  return result;
}

template<typename T>
sk::util::Items<T>
sk::util::Items<T>::
operator + (const T& item) const
{
  Items<T> array(*this);
  return array << item;
}

template<typename T>
struct sk::util::Items<T>::Propagator : public virtual sk::util::Processor<const T> {
  Propagator(sk::util::Items<T>& destination)
    : _destination(destination) {}

  void process(const T& item) const {
    _destination << item;
  }
  sk::util::Items<T>& _destination;
};

template<typename T>
sk::util::Items<T>
sk::util::Items<T>::
operator + (const sk::util::Items<T>& other) const
{
  Items<T> array(*this);
  other.forEach(Propagator(array));
  return array;
}

template<typename T>
sk::util::Items<T>&
sk::util::Items<T>::
operator << (const T& item)
{
  addLast(item);
  return *this;
}

template<typename T>
sk::util::Items<T>&
sk::util::Items<T>::
operator << (const sk::util::Items<T>& other)
{
  if(&other != this) {
    other.forEach(Propagator(*this));
  }
  return *this;
}

template<typename T>
const T&
sk::util::Items<T>::
first() const
{
  return super_t::getFirst();
}

template<typename T>
const T&
sk::util::Items<T>::
last() const
{
  return super_t::getLast();
}

template<typename T>
const T
sk::util::Items<T>::
shift()
{
  T item = super_t::getFirst();
  super_t::removeFirst();

  return item;
}

template<typename T>
const T
sk::util::Items<T>::
pop()
{
  T item = super_t::getLast();
  super_t::removeLast();

  return item;
}

template<typename T>
const sk::util::Items<T>
sk::util::Items<T>::
slice(int start, int end) const
{
  sk::util::Items<T> result;
  forEach(sk::util::processor::Slicing<const T>(start, end, sk::util::processor::Copying<T>(result)));

  return result;
}

template<typename T>
const sk::util::Items<T>
sk::util::Items<T>::
slice(int end) const
{
  return slice(0, end);
}

#endif /* _SK_UTIL_ITEMS_CXX_ */

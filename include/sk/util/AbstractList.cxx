/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_CXX_
#define _SK_UTIL_ABSTRACTLIST_CXX_

#include <sk/util/AbstractList.hxx>
#include <sk/util/AbstractCollection.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/StringArray.h>
#include <sk/util/Validator.h>
#include <sk/util/selector/EqualPointer.hxx>

template<typename T, typename Policy>
sk::util::AbstractList<T, Policy>::
AbstractList()
{
}

template<typename T, typename Policy>
sk::util::AbstractList<T, Policy>::
~AbstractList()
{
}

template<typename T, typename Policy>
const sk::util::Class 
sk::util::AbstractList<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractList");
}

template<typename T, typename Policy>
bool
sk::util::AbstractList<T, Policy>::
add(const T& object) 
{
  add(size(), object);
  return true;
}

template<typename T, typename Policy>
bool
sk::util::AbstractList<T, Policy>::
add(T& object) 
{
  add(size(), object);
  return true;
}

template<typename T, typename Policy>
bool
sk::util::AbstractList<T, Policy>::
add(T* object) 
{
  add(size(), object);
  return true;
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
add(int /*index*/, const T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
add(int /*index*/, T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
add(int /*index*/, T* /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
struct sk::util::AbstractList<T, Policy>::IndexSelector : public virtual sk::util::Selector<T> {
  IndexSelector(int index, int size) : _index(index) {
    sk::util::Validator::ensureIndex(index, size);
  }

  bool assess(const T& object) const {
    return _index-- == 0;
  }
  mutable int _index;
};

template<typename T, typename Policy>
const T& 
sk::util::AbstractList<T, Policy>::
get(int index) const 
{
  return get(IndexSelector(index, size()));
}

template<typename T, typename Policy>
T& 
sk::util::AbstractList<T, Policy>::
getMutable(int index) const
{
  return getMutable(IndexSelector(index, size()));
}

template<typename T, typename Policy>
int 
sk::util::AbstractList<T, Policy>::
indexOf(const T& object) const 
{
  return indexOf(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy>
struct sk::util::AbstractList<T, Policy>::IndexScanningSelector : public virtual sk::util::Selector<T> {
  IndexScanningSelector(const sk::util::Selector<T>& selector, int& index, bool terminate)
    : _selector(selector), _index(index), _terminate(terminate), _counter(0) {}

  bool assess(const T& item) const {
    const int current = _counter++;
    if(_selector.assess(item) == true) {
      _index = current;
      return _terminate;
    }
    return false;
  }
  const sk::util::Selector<T>& _selector;
  int& _index;
  const bool _terminate;
  mutable int _counter;
};

template<typename T, typename Policy>
int 
sk::util::AbstractList<T, Policy>::
indexOf(const sk::util::Selector<T>& selector) const 
{
  int index = -1;
  contains(IndexScanningSelector(selector, index, true));
  return index;
}

template<typename T, typename Policy>
int 
sk::util::AbstractList<T, Policy>::
lastIndexOf(const T& object) const 
{
  return lastIndexOf(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy>
int 
sk::util::AbstractList<T, Policy>::
lastIndexOf(const Selector<T>& selector) const 
{
  int index = -1;
  contains(IndexScanningSelector(selector, index, false));
  return index;
}

template<typename T, typename Policy>
void
sk::util::AbstractList<T, Policy>::
remove(int index) 
{
  remove(IndexSelector(index, size()));
}

template<typename T, typename Policy>
T* 
sk::util::AbstractList<T, Policy>::
cutoff(int index) 
{
  return cutoff(IndexSelector(index, size()));
}

template<typename T, typename Policy>
T* 
sk::util::AbstractList<T, Policy>::
release(int index) 
{
  return release(IndexSelector(index, size()));
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
set(int index, const T& object) 
{
  remove(index);
  add(index, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
set(int index, T& object) 
{
  remove(index);
  add(index, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
set(int index, T* object) 
{
  remove(index);
  add(index, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
sort()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
shuffle()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
reverse()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
struct sk::util::AbstractList<T, Policy>::InspectingSlotProcessor : public virtual sk::util::Processor<const typename Policy::slot_t> {
  InspectingSlotProcessor(sk::util::StringArray& depot)
    : _depot(depot), _index(0) {}

  void process(const typename Policy::slot_t& slot) const {
    _depot << (sk::util::String::valueOf(_index++) + slot.inspect());
  }
  sk::util::StringArray& _depot;
  mutable int _index;
};

template<typename T, typename Policy>
const sk::util::String 
sk::util::AbstractList<T, Policy>::
inspect() const
{
  if(isEmpty() == true) {
    return "[]";
  }
  sk::util::StringArray depot;
  forEachSlot(InspectingSlotProcessor(depot));
  return "[" + sk::util::String::valueOf(size()) + ": " + depot.join(", ") + " ]";
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addFirst(const T& object)
{
  add(0, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addFirst(T& object)
{
  add(0, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addFirst(T* object)
{
  add(0, object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addLast(const T& object)
{
  add(object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addLast(T& object)
{
  add(object);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
addLast(T* object)
{
  add(object);
}

template<typename T, typename Policy>
const T& 
sk::util::AbstractList<T, Policy>::
getFirst() const
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return get(0);
}

template<typename T, typename Policy>
const T& 
sk::util::AbstractList<T, Policy>::
getLast() const
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return get(size() - 1);
}

template<typename T, typename Policy>
T& 
sk::util::AbstractList<T, Policy>::
getMutableFirst() const
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return getMutable(0);
}

template<typename T, typename Policy>
T& 
sk::util::AbstractList<T, Policy>::
getMutableLast() const
{
  if(isEmpty() == true) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return getMutable(size() - 1);
}

#endif /* _SK_UTIL_ABSTRACTLIST_CXX_ */

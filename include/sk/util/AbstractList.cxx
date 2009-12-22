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
#include <sk/util/selector/EqualPointer.cxx>

template<class T>
sk::util::AbstractList<T>::
AbstractList()
{
}

template<class T>
sk::util::AbstractList<T>::
~AbstractList()
{
}

template<class T>
const sk::util::Class 
sk::util::AbstractList<T>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractList");
}

template<class T>
bool
sk::util::AbstractList<T>::
add(const T& object) 
{
  add(size(), object);
  return true;
}

template<class T>
bool
sk::util::AbstractList<T>::
add(T& object) 
{
  add(size(), object);
  return true;
}

template<class T>
bool
sk::util::AbstractList<T>::
add(T* object) 
{
  add(size(), object);
  return true;
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int /*index*/, const T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int /*index*/, T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int /*index*/, T* /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void
sk::util::AbstractList<T>::
ensureIndex(int index, int size)
{
  if((index < 0) || (index >= size)) {
    throw sk::util::IndexOutOfBoundsException("index=" + sk::util::String::valueOf(index) + ", size=" + sk::util::String::valueOf(size));
  }
}

template<class T>
struct sk::util::AbstractList<T>::IndexSelector : public virtual sk::util::Selector<T> {
  IndexSelector(int index, int size) : _index(index) {
    sk::util::AbstractList<T>::ensureIndex(index, size);
  }

  bool assess(const T& object) const {
    return _index-- == 0;
  }
  mutable int _index;
};

template<class T>
const T& 
sk::util::AbstractList<T>::
get(int index) const 
{
  return get(IndexSelector(index, size()));
}

template<class T>
T& 
sk::util::AbstractList<T>::
getMutable(int index) 
{
  return getMutable(IndexSelector(index, size()));
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const T& object) const 
{
  return indexOf(sk::util::selector::EqualPointer<T>(object));
}

template<typename T>
struct sk::util::AbstractList<T>::IndexScanningSelector : public virtual sk::util::Selector<T> {
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

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const sk::util::Selector<T>& selector) const 
{
  int index = -1;
  contains(IndexScanningSelector(selector, index, true));
  return index;
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const T& object) const 
{
  return lastIndexOf(sk::util::selector::EqualPointer<T>(object));
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const Selector<T>& selector) const 
{
  int index = -1;
  contains(IndexScanningSelector(selector, index, false));
  return index;
}

template<class T>
void
sk::util::AbstractList<T>::
remove(int index) 
{
  remove(IndexSelector(index, size()));
}

template<class T>
T* 
sk::util::AbstractList<T>::
cutoff(int index) 
{
  return cutoff(IndexSelector(index, size()));
}

template<class T>
T* 
sk::util::AbstractList<T>::
release(int index) 
{
  return release(IndexSelector(index, size()));
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, const T& object) 
{
  remove(index);
  add(index, object);
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T& object) 
{
  remove(index);
  add(index, object);
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T* object) 
{
  remove(index);
  add(index, object);
}

template<class T>
void 
sk::util::AbstractList<T>::
sort()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
shuffle()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
reverse()
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T>
struct sk::util::AbstractList<T>::InspectingSlotProcessor : public virtual sk::util::Processor<const sk::util::Slot<T> > {
  InspectingSlotProcessor(sk::util::StringArray& depot)
    : _depot(depot), _index(0) {}

  void process(const sk::util::Slot<T>& slot) const {
    _depot << (sk::util::String::valueOf(_index++) + slot.inspect());
  }
  sk::util::StringArray& _depot;
  mutable int _index;
};

template<class T>
const sk::util::String 
sk::util::AbstractList<T>::
inspect() const
{
  if(isEmpty() == true) {
    return "[]";
  }
  sk::util::StringArray depot;
  forEachSlot(InspectingSlotProcessor(depot));
  return "[" + sk::util::String::valueOf(size()) + ": " + depot.join(", ") + " ]";
}

#endif /* _SK_UTIL_ABSTRACTLIST_CXX_ */

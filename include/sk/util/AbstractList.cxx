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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/Break.h>
#include <sk/util/StringArray.h>
#include <sk/util/slot/Processor.h>
#include <sk/util/selector/Same.cxx>

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
const T& 
sk::util::AbstractList<T>::
get(int index) const 
{
  if((index < 0) || (index >= size())) {
    throw sk::util::IndexOutOfBoundsException(SK_METHOD);
  }
  struct Processor : public virtual sk::util::Processor<const T> {
    Processor(sk::util::Holder<const T>& holder, int& index)
      : _holder(holder), _index(index) {}

    void process(const T& object) const {
      if(_index-- == 0) {
        _holder.set(object);
        throw sk::util::Break();
      }
    }
    sk::util::Holder<const T>& _holder;
    int& _index;
  };
  sk::util::Holder<const T> holder;
  forEach(Processor(holder, index));
  return holder.get();
}

template<class T>
T& 
sk::util::AbstractList<T>::
getMutable(int index) 
{
  if((index < 0) || (index >= size())) {
    throw sk::util::IndexOutOfBoundsException(SK_METHOD);
  }
  struct Processor : public virtual sk::util::Processor<T> {
    Processor(sk::util::Holder<T>& holder, int& index)
      : _holder(holder), _index(index) {}

    void process(T& object) const {
      if(_index-- == 0) {
        _holder.set(object);
        throw sk::util::Break();
      }
    }
    sk::util::Holder<T>& _holder;
    int& _index;
  };
  sk::util::Holder<T> holder;
  forEach(Processor(holder, index));
  return holder.get();
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const T& object) const 
{
  return indexOf(sk::util::selector::Same<T>(object));
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const Selector<T>& /*selector*/) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const T& object) const 
{
  return lastIndexOf(sk::util::selector::Same<T>(object));
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const Selector<T>& /*selector*/) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void
sk::util::AbstractList<T>::
remove(int /*index*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractList<T>::
cutoff(int /*index*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractList<T>::
release(int /*index*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int /*index*/, const T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int /*index*/, T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int /*index*/, T* /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
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
struct sk::util::AbstractList<T>::InspectingSlotProcessor : public virtual sk::util::slot::Processor<const T> {
  InspectingSlotProcessor(sk::util::StringArray& depot)
    : _depot(depot), _index(0) {}

  bool process(const sk::util::Slot<const T>& slot) const {
    _depot << (sk::util::String::valueOf(_index++) + slot.inspect());
    return false;
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
  forEachSlot(typename sk::util::AbstractList<T>::InspectingSlotProcessor(depot));
  return "[" + sk::util::String::valueOf(size()) + ": " + depot.join(", ") + " ]";
}

#endif /* _SK_UTIL_ABSTRACTLIST_CXX_ */

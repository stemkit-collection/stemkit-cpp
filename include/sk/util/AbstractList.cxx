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
#include <sk/util/Validator.h>
#include <sk/util/selector/EqualPointer.hxx>
#include <sk/util/mapper/Stringing.hxx>
#include <sk/util/Injector.cxx>
#include <sk/util/reducer/Join.hxx>
#include <sk/util/Lists.hxx>

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
const sk::util::String 
sk::util::AbstractList<T, Policy>::
inspect() const
{
  sk::util::String depot;
  int index;

  typename sk::util::Lists<T, Policy>::SlotInspector inspector(depot, index);
  forEachSlot(inspector);

  return inspector.collect();
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
  sk::util::Validator::ensureNotEmpty(size());
  return get(0);
}

template<typename T, typename Policy>
const T& 
sk::util::AbstractList<T, Policy>::
getLast() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return get(size() - 1);
}

template<typename T, typename Policy>
T& 
sk::util::AbstractList<T, Policy>::
getMutableFirst() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return getMutable(0);
}

template<typename T, typename Policy>
T& 
sk::util::AbstractList<T, Policy>::
getMutableLast() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return getMutable(size() - 1);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
removeFirst()
{
  sk::util::Validator::ensureNotEmpty(size());
  remove(0);
}

template<typename T, typename Policy>
void 
sk::util::AbstractList<T, Policy>::
removeLast()
{
  sk::util::Validator::ensureNotEmpty(size());
  remove(size() - 1);
}

template<typename T, typename Policy>
T*
sk::util::AbstractList<T, Policy>::
cutoffFirst()
{
  sk::util::Validator::ensureNotEmpty(size());
  return cutoff(0);
}

template<typename T, typename Policy>
T*
sk::util::AbstractList<T, Policy>::
cutoffLast()
{
  sk::util::Validator::ensureNotEmpty(size());
  return cutoff(size() - 1);
}

template<typename T, typename Policy>
const sk::util::String 
sk::util::AbstractList<T, Policy>::
join(const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper) const
{
  return sk::util::Injector<T, sk::util::String>(*this).inject(mapper, sk::util::reducer::Join<T, sk::util::String>(separator));
}

template<typename T, typename Policy>
const sk::util::String 
sk::util::AbstractList<T, Policy>::
join(const sk::util::String& separator) const
{
  return join(separator, sk::util::mapper::Stringing<T>());
}

template<typename T, typename Policy>
const sk::util::String 
sk::util::AbstractList<T, Policy>::
join() const
{
  return join("", sk::util::mapper::Stringing<T>());
}

#endif /* _SK_UTIL_ABSTRACTLIST_CXX_ */

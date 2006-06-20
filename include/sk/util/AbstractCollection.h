/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_
#define _SK_UTIL_ABSTRACTCOLLECTION_

#include <sk/util/Collection.h>
#include <sk/util/Class.h>
#include <sk/util/UnsupportedOperationException.h>

namespace sk {
  namespace util {
    template<class T>
    class AbstractCollection
      : public virtual sk::util::Collection<T>
    {
      public:
        AbstractCollection();
        virtual ~AbstractCollection();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::util::Collection<T> implementation.
        T& get(const Selector<T>& selector) const;
        void forEach(const Processor<T>& procesor) const;
        bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const;
        bool isEmpty() const;
        int size() const;
        bool contains(const T& object) const;
        bool contains(const Selector<T>& selector) const;
        bool containsAll(const Collection<T>& other) const;
        bool add(T& object);
        bool add(T* object);
        bool addAll(const Collection<T>& other);
        bool moveAll(const Collection<T>& other);
        void clear();
        bool remove(const T& object);
        bool remove(const Selector<T>& selector);
        T* cutoff(const T& object);
        T* cutoff(const Selector<T>& selector);
        T* release(const T& object);
        T* release(const Selector<T>& selector);
        bool removeAll(const Collection<T>& other);
        bool removeAll(const Selector<T>& selector);
        bool retainAll(const Collection<T>& other);
        bool retainAll(const Selector<T>& selector);

      private:
        AbstractCollection(const AbstractCollection<T>& other);
        AbstractCollection<T>& operator = (const AbstractCollection<T>& other);
    };
  }
}

template<class T>
sk::util::AbstractCollection<T>::
AbstractCollection()
{
}

template<class T>
sk::util::AbstractCollection<T>::
~AbstractCollection()
{
}

template<class T>
const sk::util::Class 
sk::util::AbstractCollection<T>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractCollection");
}

template<class T>
T& 
sk::util::AbstractCollection<T>::
get(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::get(selector)");
}

template<class T>
void 
sk::util::AbstractCollection<T>::
forEach(const Processor<T>& procesor) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::forEach(processor)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
find(sk::util::Holder<T>& holder, const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::find()");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
isEmpty() const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::isEmpty()");
}

template<class T>
int 
sk::util::AbstractCollection<T>::
size() const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::size()");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
contains(const T& object) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::contains(object)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
contains(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::contains(selector)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
containsAll(const Collection<T>& other) const 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::containsAll(collection)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::add(object&)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T* object) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::add(object*)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
addAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::addAll(collection)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
moveAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::moveAll(collection)");
}

template<class T>
void 
sk::util::AbstractCollection<T>::
clear() 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::clear()");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::remove(object)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const Selector<T>& selector) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::remove(selector)");
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::cutoff(object)");
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const Selector<T>& selector) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::cutoff(selector)");
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::release(object)");
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const Selector<T>& selector) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::release(selector)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::removeAll(collection)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const Selector<T>& selector) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::removeAll(selector)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::retainAll(collection)");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Selector<T>& selector) 
{
  throw UnsupportedOperationException("sk::util::AbstractCollection::retainAll(selector)");
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_ */

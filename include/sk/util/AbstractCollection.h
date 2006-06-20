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
        T& get(const Selector<T>& selector) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::get(selector)");
        }
        void forEach(const Processor<T>& procesor) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::forEach(processor)");
        }
        bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::find()");
        }
        bool isEmpty() const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::isEmpty()");
        }
        int size() const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::size()");
        }
        bool contains(const T& object) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::contains(object)");
        }
        bool contains(const Selector<T>& selector) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::contains(selector)");
        }
        bool containsAll(const Collection<T>& other) const {
          throw UnsupportedOperationException("sk::util::AbstractCollection::containsAll(collection)");
        }
        bool add(T& object) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::add(object&)");
        }
        bool add(T* object) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::add(object*)");
        }
        bool addAll(const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::addAll(collection)");
        }
        bool moveAll(const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::moveAll(collection)");
        }
        void clear() {
          throw UnsupportedOperationException("sk::util::AbstractCollection::clear()");
        }
        bool remove(const T& object) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::remove(object)");
        }
        bool remove(const Selector<T>& selector) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::remove(selector)");
        }
        T* cutoff(const T& object) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::cutoff(object)");
        }
        T* cutoff(const Selector<T>& selector) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::cutoff(selector)");
        }
        T* release(const T& object) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::release(object)");
        }
        T* release(const Selector<T>& selector) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::release(selector)");
        }
        bool removeAll(const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::removeAll(collection)");
        }
        bool removeAll(const Selector<T>& selector) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::removeAll(selector)");
        }
        bool retainAll(const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::retainAll(collection)");
        }
        bool retainAll(const Selector<T>& selector) {
          throw UnsupportedOperationException("sk::util::AbstractCollection::retainAll(selector)");
        }

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

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_ */

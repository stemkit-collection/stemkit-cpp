/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_
#define _SK_UTIL_ABSTRACTLIST_

#include <sk/util/AbstractCollection.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Class.h>
#include <sk/util/List.h>

namespace sk {
  namespace util {
    template<class T>
    class AbstractList
      : public sk::util::AbstractCollection<T>,
        public virtual sk::util::List<T> 
    {
      public:
        AbstractList();
        virtual ~AbstractList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::util::List<T> implementation.
        void add(int index, T& object) {
          throw UnsupportedOperationException("sk::util::AbstractList::add(index, object&)");
        }
        void add(int index, T* object) {
          throw UnsupportedOperationException("sk::util::AbstractList::add(index, object*)");
        }
        using AbstractCollection<T>::add;
        
        bool addAll(int index, const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractList::addAll(index, collection)");
        }
        using AbstractCollection<T>::addAll;

        bool moveAll(int index, const Collection<T>& other) {
          throw UnsupportedOperationException("sk::util::AbstractList::moveAll(index, collection)");
        }
        using AbstractCollection<T>::moveAll;

        T& get(int index) const {
          throw UnsupportedOperationException("sk::util::AbstractList::get(index)");
        }
        using AbstractCollection<T>::get;

        int indexOf(const T& object) const {
          throw UnsupportedOperationException("sk::util::AbstractList::indexOf(object)");
        }
        int indexOf(const Selector<T>& selector) const {
          throw UnsupportedOperationException("sk::util::AbstractList::indexOf(selector)");
        }

        int lastIndexOf(const T& object) const {
          throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(object)");
        }
        int lastIndexOf(const Selector<T>& selector) const {
          throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(selector)");
        }

        T& remove(int index) {
          throw UnsupportedOperationException("sk::util::AbstractList::remove(index)");
        }
        using AbstractCollection<T>::remove;

        T* cutoff(int index) {
          throw UnsupportedOperationException("sk::util::AbstractList::cutoff(index)");
        }
        using AbstractCollection<T>::cutoff;

        T* release(int index) {
          throw UnsupportedOperationException("sk::util::AbstractList::release(index)");
        }
        using AbstractCollection<T>::release;

        void set(int index, T& object) {
          throw UnsupportedOperationException("sk::util::AbstractList::set(index, object&)");
        }
        void set(int index, T* object) {
          throw UnsupportedOperationException("sk::util::AbstractList::set(index, object*)");
        }

      private:
        AbstractList(const AbstractList<T>& other);
        AbstractList<T>& operator = (const AbstractList<T>& other);
    };
  }
}

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

#endif /* _SK_UTIL_ABSTRACTLIST_ */

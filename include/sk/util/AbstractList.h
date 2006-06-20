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
        void add(int index, T& object);
        void add(int index, T* object);
        using AbstractCollection<T>::add;
        
        bool addAll(int index, const Collection<T>& other);
        using AbstractCollection<T>::addAll;

        bool moveAll(int index, Collection<T>& other);
        using AbstractCollection<T>::moveAll;

        T& get(int index) const;
        using AbstractCollection<T>::get;

        int indexOf(const T& object) const;
        int indexOf(const Selector<T>& selector) const;

        int lastIndexOf(const T& object) const;
        int lastIndexOf(const Selector<T>& selector) const;

        T& remove(int index);
        using AbstractCollection<T>::remove;

        T* cutoff(int index);
        using AbstractCollection<T>::cutoff;

        T* release(int index);
        using AbstractCollection<T>::release;

        void set(int index, T& object);
        void set(int index, T* object);

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

template<class T>
void 
sk::util::AbstractList<T>::
add(int index, T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::add(index, object&)");
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int index, T* object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::add(index, object*)");
}

template<class T>
bool 
sk::util::AbstractList<T>::
addAll(int index, const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::addAll(index, collection)");
}

template<class T>
bool 
sk::util::AbstractList<T>::
moveAll(int index, Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::moveAll(index, collection)");
}

template<class T>
T& 
sk::util::AbstractList<T>::
get(int index) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::get(index)");
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const T& object) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::indexOf(object)");
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::indexOf(selector)");
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const T& object) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(object)");
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(selector)");
}

template<class T>
T& 
sk::util::AbstractList<T>::
remove(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::remove(index)");
}

template<class T>
T* 
sk::util::AbstractList<T>::
cutoff(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::cutoff(index)");
}

template<class T>
T* 
sk::util::AbstractList<T>::
release(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::release(index)");
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::set(index, object&)");
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T* object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::set(index, object*)");
}

#endif /* _SK_UTIL_ABSTRACTLIST_ */

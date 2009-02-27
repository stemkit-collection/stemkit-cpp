/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SYNCHRONIZEDCOLLECTION_HXX_
#define _SK_RT_SYNCHRONIZEDCOLLECTION_HXX_

#include <sk/util/Collection.hxx>
#include <sk/util/Holder.hxx>
#include <sk/rt/Mutex.h>

namespace sk {
  namespace rt {
    template<typename T>
    class SynchronizedCollection 
      : public virtual sk::util::Collection<T>
    {
      public:
        SynchronizedCollection(sk::util::Collection<T>& collection);
        SynchronizedCollection(sk::util::Collection<T>* collection);
        ~SynchronizedCollection();
    
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
        bool moveAll(Collection<T>& other);
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
    
      protected:
        sk::rt::Mutex _mutex;

      private:
        SynchronizedCollection(const SynchronizedCollection<T>& other);
        SynchronizedCollection<T>& operator = (const SynchronizedCollection<T>& other);

        sk::util::Holder<sk::uitl::Collection<T> > _collectionHolder;
        sk::uitl::Collection<T>& _collection;
    };
  }
}

#endif /* _SK_RT_SYNCHRONIZEDCOLLECTION_HXX_ */

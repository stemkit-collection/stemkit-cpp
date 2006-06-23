/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_HXX_
#define _SK_UTIL_ABSTRACTCOLLECTION_HXX_

#include <sk/util/Collection.h>
#include <sk/util/Class.h>

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

      private:
        AbstractCollection(const AbstractCollection<T>& other);
        AbstractCollection<T>& operator = (const AbstractCollection<T>& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_HXX_ */

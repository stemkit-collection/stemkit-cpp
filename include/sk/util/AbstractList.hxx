/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_HXX_
#define _SK_UTIL_ABSTRACTLIST_HXX_

#include <sk/util/AbstractCollection.hxx>
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

        void remove(int index);
        using AbstractCollection<T>::remove;

        T* cutoff(int index);
        using AbstractCollection<T>::cutoff;

        T* release(int index);
        using AbstractCollection<T>::release;

        void set(int index, T& object);
        void set(int index, T* object);

        void sort();

      private:
        AbstractList(const AbstractList<T>& other);
        AbstractList<T>& operator = (const AbstractList<T>& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTLIST_HXX_ */

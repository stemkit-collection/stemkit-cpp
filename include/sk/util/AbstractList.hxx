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
        const sk::util::String inspect() const;
        
        // sk::util::List<T> implementation.
        bool add(const T& object);
        bool add(T& object);
        bool add(T* object);

        void add(int index, const T& object);
        void add(int index, T& object);
        void add(int index, T* object);

        using AbstractCollection<T>::add;
        
        const T& get(int index) const;
        T& getMutable(int index);

        using AbstractCollection<T>::get;
        using AbstractCollection<T>::getMutable;

        int indexOf(const T& object) const;
        int indexOf(const Selector<T>& selector) const;

        int lastIndexOf(const T& object) const;
        int lastIndexOf(const Selector<T>& selector) const;

        void remove(int index);
        using AbstractCollection<T>::remove;

        using AbstractCollection<T>::removeAll;
        using AbstractCollection<T>::retainAll;

        T* cutoff(int index);
        using AbstractCollection<T>::cutoff;

        T* release(int index);
        using AbstractCollection<T>::release;

        void set(int index, const T& object);
        void set(int index, T& object);
        void set(int index, T* object);

        void sort();
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        void shuffle();
        void reverse();

        using AbstractCollection<T>::forEach;
        using AbstractCollection<T>::size;
        using AbstractCollection<T>::isEmpty;

      private:
        AbstractList(const AbstractList<T>& other);
        AbstractList<T>& operator = (const AbstractList<T>& other);

        struct IndexSelector;
        struct IndexScanningSelector;
        struct InspectingSlotProcessor;
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTLIST_HXX_ */

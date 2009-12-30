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
    template<typename T, typename Policy = slot::policy::Storing<T> >
    class AbstractList
      : public sk::util::AbstractCollection<T, Policy>,
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

        using AbstractCollection<T, Policy>::add;
        
        const T& get(int index) const;
        T& getMutable(int index);

        using AbstractCollection<T, Policy>::get;
        using AbstractCollection<T, Policy>::getMutable;

        int indexOf(const T& object) const;
        int indexOf(const Selector<T>& selector) const;

        int lastIndexOf(const T& object) const;
        int lastIndexOf(const Selector<T>& selector) const;

        void remove(int index);
        using AbstractCollection<T, Policy>::remove;

        using AbstractCollection<T, Policy>::removeAll;
        using AbstractCollection<T, Policy>::retainAll;

        T* cutoff(int index);
        using AbstractCollection<T, Policy>::cutoff;

        T* release(int index);
        using AbstractCollection<T, Policy>::release;

        void set(int index, const T& object);
        void set(int index, T& object);
        void set(int index, T* object);

        void sort();
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        void shuffle();
        void reverse();

        using AbstractCollection<T, Policy>::forEach;
        using AbstractCollection<T, Policy>::size;
        using AbstractCollection<T, Policy>::isEmpty;

      private:
        AbstractList(const AbstractList<T, Policy>& other);
        AbstractList<T, Policy>& operator = (const AbstractList<T, Policy>& other);

        struct IndexSelector;
        struct IndexScanningSelector;
        struct InspectingSlotProcessor;
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTLIST_HXX_ */

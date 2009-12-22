/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ARRAYLIST_HXX_
#define _SK_UTIL_ARRAYLIST_HXX_

#include <sk/util/AbstractList.hxx>
#include <sk/util/Processor.h>
#include <sk/util/Class.h>
#include <sk/util/Slot.hxx>
#include <vector>

namespace sk {
  namespace util {
    template<class T>
    class ArrayList
      : public sk::util::AbstractList<T>
    {
      public:
        ArrayList();
        virtual ~ArrayList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::util::Collection<T> implementation.
        void clear();
        int size() const;
        bool isEmpty() const;
        bool add(const T& object);
        bool add(T& object);
        bool add(T* object);
        void add(int index, const T& object);
        void add(int index, T& object);
        void add(int index, T* object);

        bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const;
        
        const T& get(int index) const;
        using AbstractList<T>::get;

        void remove(int index);
        // using AbstractList<T>::remove;

        bool removeAll(const sk::util::Selector<T>& selector);
        using AbstractList<T>::removeAll;

        T* cutoff(int index);
        using AbstractList<T>::remove;

        void sort();
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        void shuffle();

      protected:
        void forEachSlot(const sk::util::Processor<const sk::util::Slot<T> >& processor) const;
        void forEachSlot(const sk::util::Processor<sk::util::Slot<T> >& processor);

      private:
        ArrayList(const ArrayList<T>& other);
        ArrayList<T>& operator = (const ArrayList<T>& other);

        typedef Slot<T>* item;
        typedef std::allocator<item> allocator;
        typedef std::vector<item, allocator> container;

        container _container;
    };
  }
}

#endif /* _SK_UTIL_ARRAYLIST_HXX_ */

/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
#include <deque>

#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/policy/Sharing.hxx>
#include <sk/util/slot/policy/Cloning.hxx>
#include <sk/util/slot/policy/Copying.hxx>
#include <sk/util/slot/policy/Aliasing.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy = slot::policy::Storing<T> >
    class ArrayList
      : public sk::util::AbstractList<T, Policy>
    {
      public:
        typedef ArrayList<T, slot::policy::Storing<T> > Storing;
        typedef ArrayList<T, slot::policy::Cloning<T> > Cloning;
        typedef ArrayList<T, slot::policy::Copying<T> > Copying;
        typedef ArrayList<T, slot::policy::Aliasing<T> > Aliasing;
        typedef ArrayList<T, slot::policy::Sharing<T> > Sharing;

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
        using AbstractList<T, Policy>::get;

        T& getMutable(int index);
        using AbstractList<T, Policy>::getMutable;

        void remove(int index);
        using AbstractList<T, Policy>::remove;

        bool removeAll(const sk::util::Selector<T>& selector);
        using AbstractList<T, Policy>::removeAll;

        T* cutoff(int index);
        using AbstractList<T, Policy>::cutoff;

        void sort();
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        void shuffle();
        void reverse();

      protected:
        void forEachSlot(const sk::util::Processor<const typename Policy::slot_t>& processor) const;
        void forEachSlot(const sk::util::Processor<typename Policy::slot_t>& processor);

      private:
        ArrayList(const ArrayList<T, Policy>& other);
        ArrayList<T>& operator = (const ArrayList<T, Policy>& other);

        typedef typename Policy::slot_storage_t item_t;
        typedef std::allocator<item_t> allocator_t;
        typedef std::deque<item_t, allocator_t> container_t;

        container_t _container;
    };
  }
}

#endif /* _SK_UTIL_ARRAYLIST_HXX_ */

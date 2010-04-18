/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_LINKEDLIST_HXX_
#define _SK_UTIL_LINKEDLIST_HXX_

#include <sk/util/StandardContainer.hxx>
#include <sk/util/slot/policy/Storing.hxx>
#include <list>

namespace sk {
  namespace util {
    namespace type {
      template<typename T, typename Policy>
      struct list {
        typedef typename Policy::slot_storage_t item_t;
        typedef std::list<item_t, std::allocator<item_t> > container_t;
      };
    }

    template<typename T, typename Policy = slot::policy::Storing<T> >
    class LinkedList 
      : public sk::util::StandardContainer<T, Policy, type::list<T, Policy> >
    {
      typedef type::list<T, Policy> type_t;
      typedef sk::util::StandardContainer<T, Policy, type_t> super_t;

      public:
        typedef LinkedList<T, slot::policy::Storing<T> > Storing;
        typedef LinkedList<T, slot::policy::Direct<T> > Direct;
        typedef LinkedList<T, slot::policy::Cloning<T> > Cloning;
        typedef LinkedList<T, slot::policy::Copying<T> > Copying;
        typedef LinkedList<T, slot::policy::Aliasing<T> > Aliasing;
        typedef LinkedList<T, slot::policy::Sharing<T> > Sharing;

      public:
        LinkedList();
        ~LinkedList();
    
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        using super_t::sort;

        void shuffle();
        void reverse();

        void addFirst(const T& object);
        void addFirst(T& object);
        void addFirst(T* object);

        void removeFirst();
        T* cutoffFirst();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_LINKEDLIST_HXX_ */

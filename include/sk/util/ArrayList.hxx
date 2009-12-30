/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ARRAYLIST_HXX_
#define _SK_UTIL_ARRAYLIST_HXX_

#include <sk/util/StandardContainer.hxx>
#include <sk/util/slot/policy/Storing.hxx>
#include <deque>

namespace sk {
  namespace util {
    namespace type {
      template<typename T, typename Policy>
      struct deque {
        typedef typename Policy::slot_storage_t item_t;
        typedef std::deque<item_t, std::allocator<item_t> > container_t;
      };
    }

    template<typename T, typename Policy = slot::policy::Storing<T> >
    class ArrayList 
      : public sk::util::StandardContainer<T, Policy, type::deque<T, Policy> >
    {
      public:
        typedef ArrayList<T, slot::policy::Storing<T> > Storing;
        typedef ArrayList<T, slot::policy::Cloning<T> > Cloning;
        typedef ArrayList<T, slot::policy::Copying<T> > Copying;
        typedef ArrayList<T, slot::policy::Aliasing<T> > Aliasing;
        typedef ArrayList<T, slot::policy::Sharing<T> > Sharing;

      public:
        ArrayList();
        ~ArrayList();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        ArrayList(const ArrayList<T, Policy>& other);
        ArrayList<T, Policy>& operator = (const ArrayList<T, Policy>& other);
    };
  }
}

#endif /* _SK_UTIL_ARRAYLIST_HXX_ */

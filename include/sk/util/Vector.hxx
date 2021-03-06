/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_VECTOR_HXX_
#define _SK_UTIL_VECTOR_HXX_

#include <sk/util/RandomAccessContainer.hxx>
#include <sk/util/slot/policy/Storing.hxx>
#include <vector>

namespace sk {
  namespace util {
    namespace type {
      template<typename T, typename Policy>
      struct vector {
        typedef typename Policy::slot_storage_t item_t;
        typedef std::vector<item_t, std::allocator<item_t> > container_t;
      };
    }

    template<typename T, typename Policy = slot::policy::Storing<T> >
    class Vector
      : public sk::util::RandomAccessContainer<T, Policy, type::vector<T, Policy> >
    {
      typedef type::vector<T, Policy> type_t;
      typedef sk::util::RandomAccessContainer<T, Policy, type_t> super_t;

      public:
        typedef Vector<T, slot::policy::Storing<T> > Storing;
        typedef Vector<T, slot::policy::Direct<T> > Direct;
        typedef Vector<T, slot::policy::Cloning<T> > Cloning;
        typedef Vector<T, slot::policy::Copying<T> > Copying;
        typedef Vector<T, slot::policy::Aliasing<T> > Aliasing;
        typedef Vector<T, slot::policy::Sharing<T> > Sharing;

      public:
        Vector();
        ~Vector();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_VECTOR_HXX_ */

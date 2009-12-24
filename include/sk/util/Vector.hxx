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

#include <sk/util/StandardContainer.hxx>
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
      : public sk::util::StandardContainer<T, Policy, type::vector<T, Policy> >
    {
      public:
        Vector();
        ~Vector();
    
      private:
        Vector(const Vector<T, Policy>& other);
        Vector<T, Policy>& operator = (const Vector<T, Policy>& other);

        typedef typename type::vector<T, Policy>::item_t item_t;
        typedef typename type::vector<T, Policy>::container_t container_t;
    };
  }
}

#endif /* _SK_UTIL_VECTOR_HXX_ */

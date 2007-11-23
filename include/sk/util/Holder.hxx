/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/slot/Reference.hxx>
#include <sk/util/slot/Pointer.hxx>
#include <sk/util/slot/mixin/None.h>
#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/policy/Sharing.hxx>
#include <sk/util/slot/policy/Cloning.hxx>
#include <sk/util/slot/policy/Aliasing.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy = slot::policy::Storing<T> >
    class Holder
      : public Policy
    {
      public:
        typedef Holder<T, slot::policy::Sharing<T> > Sharing;
        typedef Holder<T, slot::policy::Cloning<T> > Cloning;
        typedef Holder<T, slot::policy::Aliasing<T> > Aliasing;

      public:
        Holder();
        explicit Holder(T* object);
        explicit Holder(T& object);
        virtual ~Holder();

        bool contains(const T& object) const;
        bool isEmpty() const;
        bool isOwner() const;
        T& get() const;

        Holder<T, Policy>& set(T* object);
        Holder<T, Policy>& set(T& object);

        bool remove();
        void clear();

        T* release();
        
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

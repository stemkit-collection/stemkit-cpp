/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/slot/mixin/None.h>
#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/policy/Sharing.hxx>
#include <sk/util/slot/policy/Cloning.hxx>
#include <sk/util/slot/policy/Copying.hxx>
#include <sk/util/slot/policy/Aliasing.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy = slot::policy::Storing<T> >
    class Holder
      : public virtual sk::util::Object
    {
      public:
        typedef Holder<T, slot::policy::Sharing<T> > Sharing;
        typedef Holder<T, slot::policy::Cloning<T> > Cloning;
        typedef Holder<T, slot::policy::Copying<T> > Copying;
        typedef Holder<T, slot::policy::Aliasing<T> > Aliasing;

      public:
        Holder();
        Holder(const Holder<T, Policy>& other);

        explicit Holder(T* object);
        explicit Holder(T& object);
        explicit Holder(const T& object);
        virtual ~Holder();

        Holder<T, Policy>& operator=(const Holder<T, Policy>& other);

        bool contains(const T& object) const;
        bool isEmpty() const;
        bool isOwner() const;
        const T& get() const;
        T& getMutable();

        void set(T* object);
        void set(T& object);
        void set(const T& object);

        bool remove();
        void clear();

        T* release();
        T* deprive();

        // sk::util::Object re-implementation.
        const sk::util::String inspect() const;

      private:
        typename Policy::slot_storage_type _storage;
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

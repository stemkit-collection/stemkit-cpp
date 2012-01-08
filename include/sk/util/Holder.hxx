/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/Object.h>

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
        typedef Holder<T, slot::policy::Storing<T> > Storing;
        typedef Holder<T, slot::policy::Direct<T> > Direct;
        typedef Holder<T, slot::policy::Cloning<T> > Cloning;
        typedef Holder<T, slot::policy::Copying<T> > Copying;
        typedef Holder<T, slot::policy::Aliasing<T> > Aliasing;
        typedef Holder<T, slot::policy::Sharing<T> > Sharing;

      public:
        Holder();
        Holder(const Storing& other);
        Holder(const Direct& other);
        Holder(const Copying& other);
        Holder(const Cloning& other);
        Holder(const Aliasing& other);
        Holder(const Sharing& other);

        explicit Holder(T* object);
        explicit Holder(T& object);
        explicit Holder(const T& object);
        virtual ~Holder();

        Holder<T, Policy>& operator=(const Storing& other);
        Holder<T, Policy>& operator=(const Direct& other);
        Holder<T, Policy>& operator=(const Copying& other);
        Holder<T, Policy>& operator=(const Cloning& other);
        Holder<T, Policy>& operator=(const Aliasing& other);
        Holder<T, Policy>& operator=(const Sharing& other);

        const typename Policy::slot_t& getSlot() const;

        bool contains(const T& object) const;
        bool isEmpty() const;
        bool isOwner() const;
        bool isMutable() const;

        const T& get() const;
        T& getMutable() const;

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
        friend class Holder<T, slot::policy::Storing<T> >;
        friend class Holder<T, slot::policy::Direct<T> >;
        friend class Holder<T, slot::policy::Copying<T> >;
        friend class Holder<T, slot::policy::Cloning<T> >;
        friend class Holder<T, slot::policy::Aliasing<T> >;
        friend class Holder<T, slot::policy::Sharing<T> >;

        typename Policy::slot_storage_t _storage;
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/Slot.hxx>

namespace sk {
  namespace util {
    template<typename T>
    class Holder
    {
      public:
        Holder();
        explicit Holder(T* object);
        explicit Holder(T& object);
        virtual ~Holder();

        bool contains(const T& object) const;
        bool isEmpty() const;
        bool isOwner() const;
        T& get() const;

        Holder<T>& set(T* object);
        Holder<T>& set(T& object);

        bool remove();
        void clear();

        T* release();
        
      private:
        Holder(const Holder<T>& other);
        Holder<T>& operator = (const Holder<T>& other);
        Holder<T>& set(const Holder<T>& other);

        Slot<T>* _slot;
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

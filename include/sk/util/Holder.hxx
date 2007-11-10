/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/MixableSlot.hxx>

namespace sk {
  namespace util {
    struct DefaultPolicy {};

    template<typename T, typename Policy = DefaultPolicy, typename SlotActions = DefaultSlotMixin>
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

        Holder<T, Policy, SlotActions>& set(T* object);
        Holder<T, Policy, SlotActions>& set(T& object);

        bool remove();
        void clear();

        T* release();
        
      private:
        Holder(const Holder<T, Policy, SlotActions>& other);
        Holder<T, Policy, SlotActions>& operator = (const Holder<T, Policy, SlotActions>& other);
        Holder<T, Policy, SlotActions>& set(const Holder<T, Policy, SlotActions>& other);

        MixableSlot<T, SlotActions>* _slot;
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

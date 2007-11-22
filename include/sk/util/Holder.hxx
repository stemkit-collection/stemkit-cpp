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
    struct ReferenceCountingMixin {
      ReferenceCountingMixin() 
        : _counter(0) {}

      bool increase() {
        return _counter++ == 0;
      }
      bool decrease() {
        return _counter > 0 ? --_counter == 0 : true;
      }
      int _counter;
    };

    template<typename T, typename SlotActions = DefaultSlotMixin>
    struct StoringPolicy 
    {
      StoringPolicy() : _slot(0) {}
      MixableSlot<T, SlotActions>* _slot;
    };

    template<typename T>
    struct SharingPolicy : public StoringPolicy<T, ReferenceCountingMixin> {
    };

    template<typename T>
    struct CloningPolicy : public StoringPolicy<T> {
    };

    template<typename T>
    struct AliasingPolicy : public StoringPolicy<T> {
    };

    template<typename T, typename Policy = StoringPolicy<T> >
    class Holder
      : public Policy
    {
      public:
        typedef Holder<T, SharingPolicy<T> > Sharing;
        typedef Holder<T, CloningPolicy<T> > Cloning;
        typedef Holder<T, AliasingPolicy<T> > Aliasing;

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
        
      private:
        Holder(const Holder<T, Policy>& other);
        Holder<T, Policy>& operator = (const Holder<T, Policy>& other);
        Holder<T, Policy>& set(const Holder<T, Policy>& other);
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

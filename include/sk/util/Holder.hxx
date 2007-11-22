/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_HXX_
#define _SK_UTIL_HOLDER_HXX_

#include <sk/util/MixableSlot.hxx>
#include <sk/util/ReferenceSlot.hxx>
#include <sk/util/PointerSlot.hxx>

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
    class StoringPolicy 
    {
      protected: 
        StoringPolicy() 
          : _slot(0) {}

        void set(T& object) {
          _slot = new ReferenceSlot<T, SlotActions>(object);
        }
        void set(T* object) {
          _slot = new PointerSlot<T, SlotActions>(object);
        }
        bool isEmpty() const {
          return _slot == 0;
        }
        T& get() const {
          return _slot->get();
        }
        bool isOwner() const {
          return _slot->isOwner();
        }
        void clear() {
          delete _slot;
          _slot = 0;
        }
        T* deprive() {
          return _slot->deprive();
        }

      private:
        StoringPolicy(const StoringPolicy<T, SlotActions>& other);
        StoringPolicy<T, SlotActions>& operator = (const StoringPolicy<T, SlotActions>& other);

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
        
    };
  }
}

#endif /* _SK_UTIL_HOLDER_HXX_ */

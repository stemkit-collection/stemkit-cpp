/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_STORING_HXX_
#define _SK_UTIL_SLOT_POLICY_STORING_HXX_

#include <sk/util/slot/Mixable.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T, typename SlotMixin = slot::mixin::None>
        class Storing
        {
          protected: 
            Storing() 
              : _slot(0) {}

            void set(T& object) {
              _slot = new slot::Reference<T, SlotMixin>(object);
            }

            void set(T* object) {
              _slot = new slot::Pointer<T, SlotMixin>(object);
            }

            bool hasSlot() const {
              return _slot != 0;
            }

            void clearSlot() {
              delete _slot;
              _slot = 0;
            }

            const slot::Mixable<T, SlotMixin>& getSlot() const {
              return *_slot;
            }

            slot::Mixable<T, SlotMixin>& getSlot() {
              return *_slot;
            }

          private:
            Storing(const Storing<T, SlotMixin>& other);
            Storing<T, SlotMixin>& operator = (const Storing<T, SlotMixin>& other);

            slot::Mixable<T, SlotMixin>* _slot;
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_STORING_HXX_ */

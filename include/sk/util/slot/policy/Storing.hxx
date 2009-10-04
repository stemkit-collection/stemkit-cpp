/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_STORING_HXX_
#define _SK_UTIL_SLOT_POLICY_STORING_HXX_

#include <sk/util/slot/Mixable.hxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/slot/Reference.hxx>
#include <sk/util/slot/Pointer.hxx>

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

            void setSlot(slot::Mixable<T, SlotMixin>* slot) {
              _slot = slot;
            }

            void setObject(T& object) {
              clearSlot();
              setSlot(new slot::Reference<T, SlotMixin>(object));
            }

            void setObject(T* object) {
              clearSlot();
              if(object != 0) {
                setSlot(new slot::Pointer<T, SlotMixin>(object));
              }
            }

            bool hasSlot() const {
              return _slot != 0;
            }

            static bool hasSlot(const Storing<T, SlotMixin>& other) {
              return other.hasSlot();
            }

            void clearSlot() {
              delete _slot;
              _slot = 0;
            }

            slot::Mixable<T, SlotMixin>& getSlot() const {
              if(hasSlot() == false) {
                throw MissingResourceException("sk::util::slot::policy::Storing#getSlot()");
              }
              return *_slot;
            }

            static slot::Mixable<T, SlotMixin>& getSlot(const Storing<T, SlotMixin>& other) {
              return other.getSlot();
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

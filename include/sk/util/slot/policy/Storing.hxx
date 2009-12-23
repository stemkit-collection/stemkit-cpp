/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_STORING_HXX_
#define _SK_UTIL_SLOT_POLICY_STORING_HXX_

#include <sk/util/Slot.hxx>
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
          public: 
            typedef sk::util::Slot<T, SlotMixin> slot_type;
            typedef slot_type* slot_storage_type;

            static void setSlot(slot_storage_type& storage, slot_type* slot) {
              storage = slot;
            }

            static void setObject(slot_storage_type& storage, const T& object) {
              clearSlot(storage);
              setSlot(storage, new slot::Reference<T, SlotMixin>(object));
            }

            static void setObject(slot_storage_type& storage, T& object) {
              clearSlot(storage);
              setSlot(storage, new slot::Reference<T, SlotMixin>(object));
            }

            static void setObject(slot_storage_type& storage, T* object) {
              clearSlot(storage);
              if(object != 0) {
                setSlot(storage, new slot::Pointer<T, SlotMixin>(object));
              }
            }

            static bool hasSlot(const slot_storage_type& storage) {
              return storage != 0;
            }

            static void clearSlot(slot_storage_type& storage) {
              delete storage;
              storage = 0;
            }

            static sk::util::Slot<T, SlotMixin>& getSlot(const slot_storage_type& storage) {
              if(hasSlot(storage) == false) {
                throw MissingResourceException("sk::util::slot::policy::Storing#getSlot()");
              }
              return *storage;
            }

          protected:
            Storing();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_STORING_HXX_ */

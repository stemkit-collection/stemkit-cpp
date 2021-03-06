/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_STORING_HXX_
#define _SK_UTIL_SLOT_POLICY_STORING_HXX_

#include <sk/util/Slot.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/slot/Reference.cxx>
#include <sk/util/slot/Pointer.cxx>
#include <sk/util/selector/EqualPointer.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T, typename SlotMixin = slot::mixin::None>
        class Storing
        {
          public:
            typedef sk::util::Slot<T, SlotMixin> slot_t;
            typedef slot_t* slot_storage_t;
            typedef const slot_t* const_slot_storage_t;
            typedef sk::util::selector::EqualPointer<T> equal_selector_t;

            static const T& getObject(const const_slot_storage_t storage) {
              return getConstSlot(storage).get();
            }

            static T& getMutableObject(const slot_storage_t storage) {
              return getSlot(storage).getMutable();
            }

            static bool isObjectOwner(const slot_storage_t storage) {
              return getSlot(storage).isOwner();
            }

            static T* depriveObject(const slot_storage_t storage) {
              return getSlot(storage).deprive();
            }

            static const sk::util::String inspectSlot(const const_slot_storage_t storage) {
              return getConstSlot(storage).inspect();
            }

            static void setSlot(slot_storage_t& storage, slot_t* slot) {
              storage = slot;
            }

            // Deliberately leaving this method here instead of moving it to
            // the aliasing one even though it is dangerous in a way that it
            // allows adding references to temporaries. Otherwise it would
            // require too many changes and interface adjustments.
            static void setObject(slot_storage_t& storage, const T& object) {
              clearSlot(storage);
              setSlot(storage, new slot::Reference<T, SlotMixin>(object));
            }

            static void setObject(slot_storage_t& storage, T& object) {
              clearSlot(storage);
              setSlot(storage, new slot::Reference<T, SlotMixin>(object));
            }

            static void setObject(slot_storage_t& storage, T* object) {
              clearSlot(storage);
              if(object != 0) {
                setSlot(storage, new slot::Pointer<T, SlotMixin>(object));
              }
            }

            static bool hasObject(const slot_storage_t storage) {
              if(hasSlot(storage) == true) {
                return getSlot(storage).isEmpty() == false;
              }
              return false;
            }

            static bool hasMutableObject(const slot_storage_t storage) {
              if(hasObject(storage) == true) {
                return getSlot(storage).isMutable();
              }
              return false;
            }

            static bool hasSlot(const const_slot_storage_t storage) {
              return storage != 0;
            }

            static void clearSlot(slot_storage_t& storage) {
              delete storage;
              storage = 0;
            }

            static slot_t& getSlot(const slot_storage_t storage) {
              if(hasSlot(storage) == false) {
                throw MissingResourceException("sk::util::slot::policy::Storing#getSlot()");
              }
              return *storage;
            }

            static const slot_t& getConstSlot(const const_slot_storage_t storage) {
              if(hasSlot(storage) == false) {
                throw MissingResourceException("sk::util::slot::policy::Storing#getConstSlot()");
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

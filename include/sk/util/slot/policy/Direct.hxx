/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_DIRECT_HXX_
#define _SK_UTIL_SLOT_POLICY_DIRECT_HXX_

#include <sk/util/MissingResourceException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/inspect.h>
#include <sk/util/selector/EqualValue.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        class Direct
        {
          public:
            typedef T slot_t;
            typedef slot_t* slot_storage_t;
            typedef const slot_t* const_slot_storage_t;
            typedef sk::util::selector::EqualValue<T> equal_selector_t;

            static const T& getObject(const const_slot_storage_t storage) {
              return getConstSlot(storage);
            }

            static T& getMutableObject(const slot_storage_t storage) {
              return getSlot(storage);
            }

            static bool isObjectOwner(const slot_storage_t storage) {
              return true;
            }

            static T* depriveObject(slot_storage_t storage) {
              T& object = getSlot(storage);
              storage = 0;

              return &object;
            }

            static const sk::util::String inspectSlot(const const_slot_storage_t storage) {
              return '*' + sk::util::inspect(getObject(storage));
            }

            static void setSlot(slot_storage_t& storage, slot_t* slot) {
              storage = slot;
            }

            static void setObject(slot_storage_t& storage, T* object) {
              clearSlot(storage);
              if(object != 0) {
                setSlot(storage, object);
              }
            }

            static void setObject(slot_storage_t& storage, const T& object) {
              throw sk::util::UnsupportedOperationException("setObject");
            }

            static void setObject(slot_storage_t& storage, T& object) {
              throw sk::util::UnsupportedOperationException("setObject");
            }

            static bool hasObject(const slot_storage_t storage) {
              return hasSlot(storage);
            }

            static bool hasMutableObject(const slot_storage_t storage) {
              return hasSlot(storage);
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
                throw MissingResourceException("sk::util::slot::policy::Direct#getSlot()");
              }
              return *storage;
            }

            static const slot_t& getConstSlot(const const_slot_storage_t storage) {
              if(hasSlot(storage) == false) {
                throw MissingResourceException("sk::util::slot::policy::Direct#getConstSlot()");
              }
              return *storage;
            }

          protected:
            Direct();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_DIRECT_HXX_ */

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
#include <sk/util/inspect.h>

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

            static const T& getObject(const slot_storage_t storage) {
              return getSlot(storage);
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

            static const sk::util::String inspectSlot(const slot_storage_t storage) {
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

            static bool hasObject(const slot_storage_t storage) {
              return hasSlot(storage) == true;
            }

            static bool hasSlot(const slot_storage_t storage) {
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

          protected:
            Direct();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_DIRECT_HXX_ */

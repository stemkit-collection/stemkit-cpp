/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_COPYING_HXX_
#define _SK_UTIL_SLOT_POLICY_COPYING_HXX_

#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/policy/Acceptor.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        struct Copying 
          : public Storing<T>
        {
          public:
            typedef Storing<T> super_t;
            typedef typename super_t::slot_t slot_t;
            typedef typename super_t::slot_storage_t slot_storage_t;

            static void setObject(slot_storage_t& storage, const T& object) {
              super_t::setObject(storage, new T(object));
            }

            static void setObject(slot_storage_t& storage, T& object) {
              super_t::setObject(storage, new T(object));
            }

            static void setObject(slot_storage_t& storage, T* object) {
              super_t::setObject(storage, object);
            }

            static void acceptSlot(slot_storage_t& storage, slot_storage_t other) {
              Acceptor<T, Copying<T> >::acceptSlot(storage, other);
            }

          protected:
            Copying();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_COPYING_HXX_ */

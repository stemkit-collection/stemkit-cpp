/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_CLONING_HXX_
#define _SK_UTIL_SLOT_POLICY_CLONING_HXX_

#include <sk/util/slot/policy/Direct.hxx>
#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/policy/Acceptor.hxx>
#include <sk/util/covariant.h>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        struct Cloning 
          : public Direct<T>
        {
          public:
            typedef Direct<T> super_t;
            typedef typename super_t::slot_t slot_t;
            typedef typename super_t::slot_storage_t slot_storage_t;

            static void setObject(slot_storage_t& storage, const T& object) {
              super_t::setObject(storage, sk::util::covariant<T>(object.clone()));
            }

            static void setObject(slot_storage_t& storage, T& object) {
              super_t::setObject(storage, sk::util::covariant<T>(object.clone()));
            }

            static void setObject(slot_storage_t& storage, T* object) {
              super_t::setObject(storage, object);
            }

            static void acceptSlot(slot_storage_t& storage, slot_storage_t other) {
              Acceptor<T, Cloning<T> >::acceptSlot(storage, other);
            }

            static void acceptSlot(slot_storage_t& storage, typename Storing<T>::slot_storage_t other) {
              Acceptor<T, Cloning<T>, Storing<T> >::acceptSlot(storage, other);
            }

          protected:
            Cloning();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_CLONING_HXX_ */

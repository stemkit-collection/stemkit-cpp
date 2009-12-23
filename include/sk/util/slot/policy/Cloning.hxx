/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_CLONING_HXX_
#define _SK_UTIL_SLOT_POLICY_CLONING_HXX_

#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/covariant.h>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        struct Cloning 
          : public Storing<T> 
        {
          public:
            static void setObject(typename Storing<T>::slot_storage_type& storage, const T& object) {
              Storing<T>::setObject(storage, sk::util::covariant<T>(object.clone()));
            }

            static void setObject(typename Storing<T>::slot_storage_type& storage, T& object) {
              Storing<T>::setObject(storage, sk::util::covariant<T>(object.clone()));
            }

            static void setObject(typename Storing<T>::slot_storage_type& storage, T* object) {
              Storing<T>::setObject(storage, object);
            }

            static void makeCopy(typename Storing<T>::slot_storage_type& storage, const typename Storing<T>::slot_storage_type& other) {
              if(storage == other) {
                return;
              }
              if(hasSlot(other) == true) {
                setObject(storage, getSlot(other).get());
              }
              else {
                clearSlot(storage);
              }
            }

          protected:
            Cloning();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_CLONING_HXX_ */

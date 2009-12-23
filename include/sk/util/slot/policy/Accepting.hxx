/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_ACCEPTING_HXX_
#define _SK_UTIL_SLOT_POLICY_ACCEPTING_HXX_

#include <sk/util/slot/policy/Storing.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T, typename Policy>
        class Accepting 
          : public Storing<T>
        {
          public:
            static void acceptSlot(typename Storing<T>::slot_storage_type& storage, typename Storing<T>::slot_storage_type other) {
              if(storage == other) {
                return;
              }
              if(Policy::hasSlot(other) == true) {
                Policy::setObject(storage, Policy::getSlot(other).get());
              }
              else {
                Policy::clearSlot(storage);
              }
            }
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_ACCEPTING_HXX_ */

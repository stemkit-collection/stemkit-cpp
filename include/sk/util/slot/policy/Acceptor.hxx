/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_ACCEPTOR_HXX_
#define _SK_UTIL_SLOT_POLICY_ACCEPTOR_HXX_

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T, typename Policy>
        class Acceptor
        {
          public:
            static void acceptSlot(typename Policy::slot_storage_t& storage, typename Policy::slot_storage_t other) {
              if(storage == other) {
                return;
              }
              if(Policy::hasSlot(other) == true) {
                Policy::setObject(storage, Policy::getObject(other));
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

#endif /* _SK_UTIL_SLOT_POLICY_ACCEPTOR_HXX_ */

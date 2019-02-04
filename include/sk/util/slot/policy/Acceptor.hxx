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
        template<typename T, typename Target, typename Source = Target>
        class Acceptor
        {
          public:
            static void acceptSlot(typename Target::slot_storage_t& storage, typename Source::slot_storage_t other) {
              if(Source::hasObject(other) == true) {
                const T& object = Source::getObject(other);
                if(Target::hasObject(storage) == true) {
                  if(&Target::getObject(storage) == &object) {
                    return;
                  }
                }
                if(Source::hasMutableObject(other) == true) {
                  Target::setObject(storage, Source::getMutableObject(other));
                }
                else {
                  Target::setObject(storage, object);
                }
                return;
              }
              Target::clearSlot(storage);
            }
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_ACCEPTOR_HXX_ */

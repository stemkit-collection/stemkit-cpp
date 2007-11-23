/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_SHARING_HXX_
#define _SK_UTIL_SLOT_POLICY_SHARING_HXX_

#include <sk/util/slot/mixin/LinkCounter.h>
#include <sk/util/slot/policy/Storing.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        class Sharing 
          : public Storing<T, slot::mixin::LinkCounter> 
        {
          public:
            Sharing() {
            }

            Sharing(const Sharing<T>& other) {
            }

            int getLinks() const {
              return Storing<T, slot::mixin::LinkCounter>::getSlot().getCounter();
            }
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_SHARING_HXX_ */

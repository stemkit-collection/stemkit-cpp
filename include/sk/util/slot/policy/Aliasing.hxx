/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_ALIASING_HXX_
#define _SK_UTIL_SLOT_POLICY_ALIASING_HXX_

#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/slot/mixin/LinkCounter.h>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        class Aliasing 
          : public Storing<T> 
        {
          public:
            Aliasing() {}

            Aliasing(const Aliasing<T>& other) {
              alias(other);
            }

            Aliasing(const Storing<T>& other) {
              alias(other);
            }

            void operator=(const Aliasing<T>& other) {
              alias(other);
            }

            void operator=(const Storing<T>& other) {
              alias(other);
            }

          private:
            void alias(const Storing<T>& other) {
              if(&other == this) {
                return;
              } 
              Storing<T>::clearSlot();

              if(hasSlot(other) == true) {
                setObject(getSlot(other).get());
              }
            }
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_ALIASING_HXX_ */

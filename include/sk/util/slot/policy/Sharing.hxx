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
          typedef Storing<T, slot::mixin::LinkCounter> Super;

          public:
            Sharing() {
            }

            Sharing(const Sharing<T>& other) {
              accept(other);
            }

            void operator=(const Sharing<T>& other) {
              accept(other);
            }

            int getLinks() const {
              return Super::getSlot().getCounter();
            }

          protected:
            void setObject(T* object) {
              Super::setObject(object);
              Super::getSlot().link();
            }
            
            void setObject(T& object) {
              Super::setObject(object);
              Super::getSlot().link();
            }

            void clearSlot() {
              if(Super::hasSlot() == true) {
                if(Super::getSlot().unlink() == true) {
                  Super::clearSlot();
                }
                else {
                  Super::setSlot(0);
                }
              }
            }

          private:
            void accept(const Sharing<T>& other) {
              if(&other == this) {
                return;
              }
              clearSlot();

              if(other.hasSlot() == true) {
                Super::setSlot(&other.getSlot());
                Super::getSlot().link();
              }
            }
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_SHARING_HXX_ */

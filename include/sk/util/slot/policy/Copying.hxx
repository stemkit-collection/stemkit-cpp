/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_COPYING_HXX_
#define _SK_UTIL_SLOT_POLICY_COPYING_HXX_

#include <sk/util/slot/policy/Storing.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        struct Copying 
          : public Storing<T> 
        {
          public:
            Copying() {
            }

            Copying(const Copying<T>& other) {
              makeCopy(other);
            }

            Copying(const Storing<T>& other) {
              makeCopy(other);
            }
            
            void operator=(const Copying<T>& other) {
              makeCopy(other);
            }

            void operator=(const Storing<T>& other) {
              makeCopy(other);
            }

          protected:
            void setObject(T& object) {
              Storing<T>::setObject(new T(object));
            }

            void setObject(T* object) {
              Storing<T>::setObject(object);
            }

            void makeCopy(const Storing<T>& other) {
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

#endif /* _SK_UTIL_SLOT_POLICY_COPYING_HXX_ */

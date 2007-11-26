/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_CLONING_HXX_
#define _SK_UTIL_SLOT_POLICY_CLONING_HXX_

#include <sk/util/slot/policy/Storing.hxx>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        struct Cloning 
          : public Storing<T> 
        {
          public:
            Cloning() {}

            Cloning(const Cloning<T>& other) {
              makeClone(other);
            }

            Cloning(const Storing<T>& other) {
              makeClone(other);
            }

            void operator=(const Cloning<T>& other) {
              makeClone(other);
            }

            void operator=(const Storing<T>& other) {
              makeClone(other);
            }
            
          protected:
            void setObject(T& object) {
              Storing<T>::setObject(object.clone());
            }

            void setObject(T* object) {
              Storing<T>::setObject(object);
            }

            void makeClone(const Storing<T>& other) {
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

#endif /* _SK_UTIL_SLOT_POLICY_CLONING_HXX_ */
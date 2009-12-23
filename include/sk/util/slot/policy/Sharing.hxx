/*  vim:sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_SHARING_HXX_
#define _SK_UTIL_SLOT_POLICY_SHARING_HXX_

#include <sk/util/slot/mixin/LinkCounter.h>
#include <sk/util/slot/policy/Storing.hxx>
#include <sk/util/IllegalStateException.h>

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
            static void setObject(typename Super::slot_storage_type& storage, T* object) {
              if(hasSlot(storage) == true) {
                if(getSlot(storage).isOwner() == false) {
                  throw sk::util::IllegalStateException("Non-replacable shared content");
                }
                delete getSlot(storage).replace(object);
              }
              else {
                Super::setObject(storage, object);
                getSlot(storage).link();
              }
            }
            
            static void setObject(typename Super::slot_storage_type& storage, T& object) {
              if(hasSlot(storage) == true) {
                throw sk::util::IllegalStateException("Non-replacable shared content");
              }
              else {
                Super::setObject(storage, object);
                getSlot(storage).link();
              }
            }

            static void setObject(typename Super::slot_storage_type& storage, const T& object) {
              if(hasSlot(storage) == true) {
                throw sk::util::IllegalStateException("Non-replacable shared content");
              }
              else {
                Super::setObject(storage, object);
                getSlot(storage).link();
              }
            }
            
            static void clearSlot(typename Super::slot_storage_type& storage) {
              if(hasSlot(storage) == true) {
                if(getSlot(storage).unlink() == true) {
                  Super::clearSlot(storage);
                }
                else {
                  setSlot(storage, 0);
                }
              }
            }

            static void makeCopy(typename Super::slot_storage_type& storage, typename Super::slot_storage_type other) {
              if(storage == other) {
                return;
              }
              if(hasSlot(other) == true) {
                setSlot(storage, &getSlot(other));
                getSlot(storage).link();
              }
              else {
                clearSlot(storage);
              }
            }

          protected:
            Sharing();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_SHARING_HXX_ */

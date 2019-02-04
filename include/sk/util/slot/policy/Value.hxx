/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POLICY_VALUE_HXX_
#define _SK_UTIL_SLOT_POLICY_VALUE_HXX_

#include <sk/util/MissingResourceException.h>
#include <sk/util/inspect.h>

namespace sk {
  namespace util {
    namespace slot {
      namespace policy {
        template<typename T>
        class Value
        {
          public: 
            typedef T slot_t;
            typedef T slot_storage_t;
            typedef const T const_slot_storage_t;

            static const sk::util::String inspectSlot(const_slot_storage_t& storage) {
              return '=' + sk::util::inspect(storage);
            }

          protected:
            Value();
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_VALUE_HXX_ */

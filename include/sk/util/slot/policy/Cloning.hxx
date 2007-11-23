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
        struct Cloning : public Storing<T> {
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_POLICY_CLONING_HXX_ */

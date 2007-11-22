/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_MIXABLE_HXX_
#define _SK_UTIL_SLOT_MIXABLE_HXX_

#include <sk/util/Slot.hxx>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T, typename Mixin>
      class Mixable
        : public virtual sk::util::Slot<T>,
          public Mixin
      {
      };
    }
  }
}

#endif /* _SK_UTIL_SLOT_MIXABLE_HXX */

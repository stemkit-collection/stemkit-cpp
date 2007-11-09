/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_MIXABLESLOT_HXX_
#define _SK_UTIL_MIXABLESLOT_HXX_

#include <sk/util/Slot.hxx>

namespace sk {
  namespace util {
    class DefautlSlotMixin
    {
    };

    template<typename T, typename Mixin = DefautlSlotMixin>
    class MixableSlot
      : public virtual sk::util::Slot<T>,
        public Mixin
    {
    };
  }
}

#endif /* _SK_UTIL_MIXABLESLOT_HXX */

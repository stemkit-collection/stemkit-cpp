/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POINTER_HXX_
#define _SK_UTIL_SLOT_POINTER_HXX_

#include <sk/util/Slot.hxx>
#include <sk/util/slot/mixin/None.h>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T, typename Mixin = mixin::None>
      class Pointer
        : public sk::util::Slot<T, Mixin>
      {
        public:
          Pointer(T* object);
          virtual ~Pointer();

          const sk::util::String inspect() const;
      };
    }
  }
}

#endif /* _SK_UTIL_SLOT_POINTER_HXX_ */

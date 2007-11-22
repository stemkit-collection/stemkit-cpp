/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_REFERENCE_HXX_
#define _SK_UTIL_SLOT_REFERENCE_HXX_

#include <sk/util/slot/Mixable.hxx>
#include <sk/util/slot/mixin/None.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T, typename Mixin = mixin::None>
      class Reference
        : public sk::util::slot::Mixable<T, Mixin>
      {
        public:
          Reference(T& object);
          virtual ~Reference();
          
          // sk::util::Slot re-implementation.
          bool isOwner() const;
          T& get() const;
          T* deprive();
          
          // sk::util::Object re-implementation.
          const sk::util::String inspect() const;
          
        private:
          Reference(const Reference<T, Mixin>& other);
          Reference<T, Mixin>& operator = (const Reference<T, Mixin>& other);

          T& _object;
      };
    }
  }
}

#endif /* _SK_UTIL_SLOT_REFERENCE_HXX_ */

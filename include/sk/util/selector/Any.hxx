/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SELECTOR_ANY_HXX_
#define _SK_UTIL_SELECTOR_ANY_HXX_

#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace selector {
      template<typename T>
      class Any : public virtual sk::util::Selector<T> {
        public:
          bool assess(const T& object) const {
            return true;
          }
      };
    }
  }
}

#endif /* _SK_UTIL_SELECTOR_ANY_HXX_ */

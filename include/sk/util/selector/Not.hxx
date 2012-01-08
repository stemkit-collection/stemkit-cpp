/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SELECTOR_NOT_HXX_
#define _SK_UTIL_SELECTOR_NOT_HXX_

#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace selector {
      template<typename T>
      class Not : public virtual sk::util::Selector<T> {
        public:
          Not(const sk::util::Selector<T>& selector)
            : _selector(selector) {}

          bool assess(const T& object) const {
            return _selector.assess(object) == false;
          }

        private:
          const sk::util::Selector<T>& _selector;
      };
    }
  }
}

#endif /* _SK_UTIL_SELECTOR_NOT_HXX_ */

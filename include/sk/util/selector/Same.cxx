/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_SELECTOR_SAME_CXX_
#define _SK_UTIL_SELECTOR_SAME_CXX_

#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace selector {
      template<typename T>
      class Same : public virtual sk::util::Selector<T> {
        public:
          Same<T>(const T& object) 
            : _object(object) {}
      
          bool assess(const T& object) const {
            return &object == &_object;
          }
      
        private:
          Same(const Same<T>& other);
          Same<T>& operator = (const Same<T>& other);

          const T& _object;
      };
    }
  }
}

#endif /* _SK_UTIL_SELECTOR_SAME_CXX_ */

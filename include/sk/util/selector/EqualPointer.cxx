/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_SELECTOR_EQUALPOINTER_CXX_
#define _SK_UTIL_SELECTOR_EQUALPOINTER_CXX_

#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace selector {
      template<typename T>
      class EqualPointer : public virtual sk::util::Selector<T> {
        public:
          EqualPointer<T>(const T& object) 
            : _object(object) {}
      
          bool assess(const T& object) const {
            return &object == &_object;
          }
      
        private:
          const T& _object;
      };
    }
  }
}

#endif /* _SK_UTIL_SELECTOR_EQUALPOINTER_CXX_ */

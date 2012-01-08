/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ASSESSOR_LESSPOINTERS_HXX_
#define _SK_UTIL_ASSESSOR_LESSPOINTERS_HXX_

#include <sk/util/Assessor.h>

namespace sk {
  namespace util {
    namespace assessor {
      template<typename T>
      class LessPointers
        : public virtual sk::util::BinaryAssessor<T>
      {
        public:
          bool assess(const T& first, const T& second) const {
            return &first < &second;
          }
      };
    }
  }
}

#endif /* _SK_UTIL_ASSESSOR_LESSPOINTERS_HXX_ */

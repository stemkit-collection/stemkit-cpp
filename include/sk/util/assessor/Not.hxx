/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ASSESSOR_NOT_HXX_
#define _SK_UTIL_ASSESSOR_NOT_HXX_

#include <sk/util/Assessor.h>

namespace sk {
  namespace util {
    namespace assessor {
      template<typename T>
      class Not 
        : public virtual sk::util::BinaryAssessor<T>
      {
        public:
          Not(const sk::util::BinaryAssessor<T>& assessor)
            : _assessor(assessor) {}
      
          bool assess(const T& first, const T& second) const {
            return not _assessor.assess(first, second);
          }
      
        private:
          const sk::util::BinaryAssessor<T>& _assessor;
      };
    }
  }
}

#endif /* _SK_UTIL_ASSESSOR_NOT_HXX_ */

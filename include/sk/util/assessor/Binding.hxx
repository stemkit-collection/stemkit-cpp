/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ASSESSOR_BINDING_HXX_
#define _SK_UTIL_ASSESSOR_BINDING_HXX_

#include <sk/util/Assessor.h>

namespace sk {
  namespace util {
    namespace assessor {
      template<typename T>
      class Binding 
        : public virtual sk::util::Assessor<T>
      {
        public:
          Binding(const T& first, const sk::util::BinaryAssessor<T>& assessor)
            : _first(first), _assessor(assessor) {}
      
          bool assess(const T& second) const {
            return _assessor.assess(_first, second);
          }
      
        private:
          const T& _first;
          const sk::util::BinaryAssessor<T>& _assessor;
      };
    }
  }
}

#endif /* _SK_UTIL_ASSESSOR_BINDING_HXX_ */

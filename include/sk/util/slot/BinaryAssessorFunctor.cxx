/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ASSESSOR_BINARYASSESSORFUNCTOR_CXX_
#define _SK_UTIL_ASSESSOR_BINARYASSESSORFUNCTOR_CXX_

#include <sk/util/Assessor.h>
#include <sk/util/Slot.hxx>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T>
      class BinaryAssessorFunctor 
      {
        public:
          BinaryAssessorFunctor(const sk::util::BinaryAssessor<T>& assessor) 
            : _assessor(assessor) {}
      
          bool operator()(const sk::util::Slot<T>* first, const sk::util::Slot<T>* second) const {
            return _assessor.assess(first->get(), second->get());
          }
      
        private:
          BinaryAssessorFunctor<T>& operator = (const BinaryAssessorFunctor<T>& other);
          
          const sk::util::BinaryAssessor<T>& _assessor;
      };
    }
  }
}

#endif /* _SK_UTIL_ASSESSOR_BINARYASSESSORFUNCTOR_CXX_ */

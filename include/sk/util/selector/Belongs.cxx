/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SELECTOR_BELONGS_CXX_
#define _SK_UTIL_SELECTOR_BELONGS_CXX_

#include <sk/util/Selector.h>
#include <sk/util/Assessor.h>
#include <sk/util/assessor/Binding.cxx>
#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    namespace selector {
      template<typename T>
      class Belongs : public virtual sk::util::Selector<T> {
        public:
          Belongs(const sk::util::Collection<T>& collection, const sk::util::BinaryAssessor<T>& assessor)
            : _collection(collection), _assessor(assessor) {}

          bool assess(const T& item) const {
            return _collection.contains(sk::util::assessor::Binding<T>(item, _assessor));
          }

        private:
          const sk::util::Collection<T>& _collection;
          const sk::util::BinaryAssessor<T>& _assessor;
      };
    }
  }
}

#endif /* _SK_UTIL_SELECTOR_BELONGS_CXX_ */

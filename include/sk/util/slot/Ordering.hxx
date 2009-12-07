/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SLOT_ORDERING_HXX_
#define _SK_UTIL_SLOT_ORDERING_HXX_

#include <sk/util/OrderingChecker.h>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T>
      class Ordering 
        : public virtual sk::util::OrderingChecker<T>
      {
        public:
          Ordering();
          Ordering(const sk::util::OrderingChecker<T>& checker);

          bool operator()(const sk::util::Slot<T>* first, const sk::util::Slot<T>* second) const;
      
        protected:
          bool isOrdered(const T& first, const T& second) const;

        private:
          const sk::util::OrderingChecker<T>& _checker;
      };
    }
  }
}

#endif /* _SK_UTIL_SLOT_ORDERING_HXX_ */

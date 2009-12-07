/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ORDERINGCHECKER_H_
#define _SK_UTIL_ORDERINGCHECKER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    template<typename T>
    class OrderingChecker 
      : public virtual sk::util::Object
    {
      public:
        virtual bool isOrdered(const T& first, const T& second) const = 0;
    };
  }
}

#endif /* _SK_UTIL_ORDERINGCHECKER_H_ */

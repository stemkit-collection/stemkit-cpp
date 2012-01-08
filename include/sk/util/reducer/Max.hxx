/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_REDUCER_MAX_HXX_
#define _SK_UTIL_REDUCER_MAX_HXX_

#include <sk/util/Reducer.h>
#include <algorithm>

namespace sk {
  namespace util {
    namespace reducer {
      template<typename F, typename T = F>
      class Max
        : public virtual sk::util::Reducer<F, T>
      {
        public:
          T reduce(const T& memo, const F& object, const sk::util::Mapper<const F, const T>& mapper) const {
            return std::max(memo, mapper.map(object));
          }
      };
    }
  }
}

#endif /* _SK_UTIL_REDUCER_MAX_HXX_ */

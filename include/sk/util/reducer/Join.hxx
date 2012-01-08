/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_REDUCER_JOIN_HXX_
#define _SK_UTIL_REDUCER_JOIN_HXX_

#include <sk/util/Reducer.h>

namespace sk {
  namespace util {
    namespace reducer {
      template<typename F, typename T = F>
      class Join
        : public virtual sk::util::Reducer<F, T>
      {
        public:
          Join()
            : _separator(0) {}

          Join(const T& separator)
            : _separator(separator) {}

          T reduce(const T& memo, const F& object, const sk::util::Mapper<const F, const T>& mapper) const {
            return memo + _separator + mapper.map(object);
          }

        private:
          const T _separator;
      };
    }
  }
}

#endif /* _SK_UTIL_REDUCER_JOIN_HXX_ */

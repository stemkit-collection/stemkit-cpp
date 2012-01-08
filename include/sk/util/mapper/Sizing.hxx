/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_MAPPER_SIZING_HXX_
#define _SK_UTIL_MAPPER_SIZING_HXX_

#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    namespace mapper {
      template<typename T>
      class Sizing : public virtual sk::util::Mapper<const T, const int> {
        public:
          const int map(const T& object) const {
            return object.size();
          }
      };
    }
  }
}

#endif /* _SK_UTIL_MAPPER_SIZING_HXX_ */

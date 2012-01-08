/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_MAPPER_COERCING_HXX_
#define _SK_UTIL_MAPPER_COERCING_HXX_

#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    namespace mapper {
      template<typename F, typename T = F>
      class Coercing : public virtual sk::util::Mapper<F, T> {
        public:
          T map(F& object) const {
            return object;
          }
      };
    }
  }
}

#endif /* _SK_UTIL_MAPPER_COERCING_HXX_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_MAPPER_STRINGING_HXX_
#define _SK_UTIL_MAPPER_STRINGING_HXX_

#include <sk/util/Mapper.h>
#include <sk/util/inspect.h>

namespace sk {
  namespace util {
    namespace mapper {
      template<typename T>
      class Stringing : public virtual sk::util::Mapper<const T, const sk::util::String> {
        public:
          const sk::util::String map(const T& object) const {
            return object.toString();
          }
      };
    }
  }
}

#endif /* _SK_UTIL_MAPPER_STRINGING_HXX_ */

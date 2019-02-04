/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_MAPPER_DOWNCASING_H_
#define _SK_UTIL_MAPPER_DOWNCASING_H_

#include <sk/util/Mapper.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    namespace mapper {
      class Downcasing : public virtual sk::util::Mapper<const sk::util::String> {
        public:
          const sk::util::String map(const sk::util::String& object) const {
            return object.toLowerCase();
          }
      };
    }
  }
}

#endif /* _SK_UTIL_MAPPER_DOWNCASING_H_ */

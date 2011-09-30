/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_TRACE_PRODUCER_H_
#define _SK_UTIL_TRACE_PRODUCER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace trace {
      class Producer 
        : public virtual sk::util::Object
      {
        public:
          virtual void setup() = 0;
          virtual const sk::util::String produceTrace() = 0;
          virtual void reset() = 0;
          virtual void finalizeFor(const sk::util::String& scope) = 0;
      };
    }
  }
}

#endif /* _SK_UTIL_TRACE_PRODUCER_H_ */

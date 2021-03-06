/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_TRACE_PRODUCERFACTORY_H_
#define _SK_UTIL_TRACE_PRODUCERFACTORY_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace trace {
      class Producer;

      class ProducerFactory
        : public virtual sk::util::Object
      {
        public:
          virtual sk::util::trace::Producer* createTraceProducer() const = 0;
      };
    }
  }
}

#endif /* _SK_UTIL_TRACE_PRODUCERFACTORY_H_ */

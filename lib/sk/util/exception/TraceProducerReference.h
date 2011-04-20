/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_EXCEPTION_TRACEPRODUCERREFERENCE_H_
#define _SK_UTIL_EXCEPTION_TRACEPRODUCERREFERENCE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace exception {
      class TraceProducerReference 
        : public virtual sk::util::Object
      {
        public:
          TraceProducerReference();
          virtual ~TraceProducerReference();

          const sk::util::String& trace();
          const sk::util::String& traceWithMessage(const sk::util::String& message);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          TraceProducerReference(const TraceProducerReference& other);
          TraceProducerReference& operator = (const TraceProducerReference& other);
      };
    }
  }
}

#endif /* _SK_UTIL_EXCEPTION_TRACEPRODUCERREFERENCE_H_ */

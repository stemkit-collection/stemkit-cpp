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
#include <sk/util/Holder.hxx>
#include <sk/util/exception/trace/Producer.h>

namespace sk {
  namespace util {
    namespace exception {
      class TraceProducerReference 
        : public virtual sk::util::Object
      {
        public:
          TraceProducerReference(sk::util::exception::trace::Producer* producer);
          virtual ~TraceProducerReference();

          int link();
          int unlink();

          const sk::util::String& trace();
          const sk::util::String& traceWithMessage(const sk::util::String& message);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          TraceProducerReference(const TraceProducerReference& other);
          TraceProducerReference& operator = (const TraceProducerReference& other);

          void ensureTraceCollected();
          void setError(const sk::util::String& message);
          void reset();

          sk::util::Holder<sk::util::exception::trace::Producer>::Direct _producerHolder;
          sk::util::exception::trace::Producer& _producer;
          sk::util::String _buffer;
          sk::util::String _trace;
          bool _traceCollected;
          int _links;
     };
    }
  }
}

#endif /* _SK_UTIL_EXCEPTION_TRACEPRODUCERREFERENCE_H_ */

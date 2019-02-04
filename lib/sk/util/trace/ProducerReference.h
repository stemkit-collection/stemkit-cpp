/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_TRACE_PRODUCERREFERENCE_H_
#define _SK_UTIL_TRACE_PRODUCERREFERENCE_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/util/trace/Producer.h>

namespace sk {
  namespace util {
    namespace trace {
      class ProducerReference 
        : public virtual sk::util::Object
      {
        public:
          ProducerReference(sk::util::trace::Producer* producer);
          virtual ~ProducerReference();

          int link();
          int unlink();

          const sk::util::String& trace();
          const sk::util::String& traceWithMessage(const sk::util::String& message);
          void finalizeFor(const sk::util::String& scope);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ProducerReference(const ProducerReference& other);
          ProducerReference& operator = (const ProducerReference& other);

          void ensureTraceCollected();
          void setError(const sk::util::String& stage, const sk::util::Strings& messages);
          void reset();

          sk::util::Holder<sk::util::trace::Producer>::Direct _producerHolder;
          sk::util::trace::Producer& _producer;
          sk::util::String _buffer;
          sk::util::String _trace;
          bool _traceCollected;
          bool _resetDone;
          int _links;
     };
    }
  }
}

#endif /* _SK_UTIL_TRACE_PRODUCERREFERENCE_H_ */

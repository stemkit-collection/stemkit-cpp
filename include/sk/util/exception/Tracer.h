/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_EXCEPTION_TRACER_H_
#define _SK_UTIL_EXCEPTION_TRACER_H_

#include <sk/util/String.h>

namespace sk {
  namespace util {
    namespace exception {
      namespace trace {
        class ProducerFactory;
      }
      class TraceProducerReference;

      class Tracer 
      {
        public:
          Tracer();
          Tracer(const Tracer& other);
          ~Tracer();

          const sk::util::String& trace() const;
          const sk::util::String& traceWithMessage(const sk::util::String& message) const;
          void finalize() const;

          static void setProducerFactory(const sk::util::exception::trace::ProducerFactory& factory);
          static void clearProducerFactory();
      
        private:
          Tracer& operator = (const Tracer& other);
          TraceProducerReference* _reference;
      };
    }
  }
}

#endif /* _SK_UTIL_EXCEPTION_TRACER_H_ */

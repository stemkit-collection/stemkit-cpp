/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_STACKTRACERFACTORY_H_
#define _SK_RT_STACKTRACERFACTORY_H_

#include <sk/util/trace/ProducerFactory.h>

namespace sk {
  namespace rt {
    class StackTracerFactory 
      : public virtual sk::util::trace::ProducerFactory
    {
      public:
        StackTracerFactory();
        virtual ~StackTracerFactory();

        // sk::util::trace::ProducerFactory implementation.
        sk::util::trace::Producer* createTraceProducer() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        sk::util::Object* clone() const;
    
      private:
        StackTracerFactory& operator = (const StackTracerFactory& other);
    };
  }
}

#endif /* _SK_RT_STACKTRACERFACTORY_H_ */

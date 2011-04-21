/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_STACKTRACEPRODUCER_H_
#define _SK_RT_STACKTRACEPRODUCER_H_

#include <sk/util/exception/trace/Producer.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    class StackTraceProducer 
      : public virtual sk::util::exception::trace::Producer
    {
      public:
        StackTraceProducer();
        virtual ~StackTraceProducer();

        // sk::util::exception::trace::Producer implementation.
        void setup();
        const sk::util::String produceTrace();
        void reset();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StackTraceProducer(const StackTraceProducer& other);
        StackTraceProducer& operator = (const StackTraceProducer& other);

        struct Data;
        sk::util::Holder<Data>::Direct _dataHolder;
        Data& _data;
    };
  }
}

#endif /* _SK_RT_STACKTRACEPRODUCER_H_ */

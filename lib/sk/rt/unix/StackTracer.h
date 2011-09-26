/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_STACKTRACER_H_
#define _SK_RT_STACKTRACER_H_

#include <sk/util/exception/trace/Producer.h>
#include <sk/rt/Scope.h>
#include <unistd.h>

namespace sk {
  namespace rt {
    class StackTracer 
      : public virtual sk::util::exception::trace::Producer
    {
      public:
        StackTracer();
        virtual ~StackTracer();

        // sk::util::exception::trace::Producer implementation.
        void setup();
        const sk::util::String produceTrace();
        void finalize();
        void reset();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StackTracer(const StackTracer& other);
        StackTracer& operator = (const StackTracer& other);

        const sk::rt::Scope _scope;
        int _channel;
        pid_t _pid;
        bool _finalizeCores;
        bool _finalizeWaits;
    };
  }
}

#endif /* _SK_RT_STACKTRACER_H_ */

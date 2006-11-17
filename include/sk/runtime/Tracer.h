/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RUNTIME_TRACER_
#define _SK_RUNTIME_TRACER_

#include <sk/util/Object.h>

namespace sk {
  namespace runtime {
    class Tracer
      : public virtual sk::util::Object 
    {
      public:
        Tracer();
        virtual ~Tracer();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Tracer(const Tracer& other);
        Tracer& operator = (const Tracer& other);
    };
  }
}

#endif /* _SK_RUNTIME_TRACER_ */

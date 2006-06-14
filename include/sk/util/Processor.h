/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_PROCESSOR_
#define _SK_UTIL_PROCESSOR_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Processor
      : public virtual sk::util::Object 
    {
      public:
        Processor();
        virtual ~Processor();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Processor(const Processor& other);
        Processor& operator = (const Processor& other);
    };
  }
}

#endif /* _SK_UTIL_PROCESSOR_ */

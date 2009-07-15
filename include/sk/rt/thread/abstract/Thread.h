/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_ABSTRACT_THREAD_H_
#define _SK_RT_THREAD_ABSTRACT_THREAD_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace abstract {
        class Thread 
          : public virtual sk::util::Object
        {
          public:
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual void interrupt() = 0;
            virtual void join() = 0;
            virtual void detach() = 0;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_ABSTRACT_THREAD_H_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_THREAD_STOPPER_H_
#define _SK_RT_THREAD_STOPPER_H_

#include <sk/util/Processor.h>
#include <sk/rt/Thread.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Stopper 
        : public virtual sk::util::Processor<sk::rt::Thread>
      {
        public:
          void process(sk::rt::Thread& thread) const {
            thread.stop();
          }
      };
    }
  }
}

#endif /* _SK_RT_THREAD_STOPPER_H_ */

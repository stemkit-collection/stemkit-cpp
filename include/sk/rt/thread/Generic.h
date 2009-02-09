/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_GENERIC_H_
#define _SK_RT_THREAD_GENERIC_H_

#include <sk/util/Object.h>
#include <sk/rt/thread/State.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Generic 
        : public virtual sk::util::Object
      {
        public:
          virtual void start() = 0;
          virtual void stop() = 0;
          virtual void join() = 0;
          virtual void interrupt() = 0;

          virtual const sk::util::String getName() const = 0;
          virtual const sk::rt::thread::State& getState() const = 0;

          virtual bool isAlive() const = 0;
          virtual bool isInterrupted() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_GENERIC_H_ */

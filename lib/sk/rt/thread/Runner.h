/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_RUNNER_H_
#define _SK_RT_THREAD_RUNNER_H_

#include <sk/rt/Runnable.h>
#include <sk/rt/thread/State.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      class Runner 
        : public virtual sk::rt::Runnable
      {
        public:
          Runner(sk::rt::Runnable& target);
          virtual ~Runner();
      
          const sk::rt::thread::State& getState() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          // sk::rt::Runnable implementation.
          void run() const;
      
        private:
          Runner(const Runner& other);
          Runner& operator = (const Runner& other);

          sk::rt::Runnable& _target;
          sk::util::Holder<const sk::rt::thread::State> _stateHolder;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_RUNNER_H_ */

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
#include <sk/rt/Scope.h>

#include <sk/rt/thread/abstract/Thread.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Runner 
        : public virtual sk::rt::Runnable
      {
        public:
          Runner(sk::rt::Runnable& target, sk::rt::thread::Generic& thread);
          virtual ~Runner();
      
          void start(sk::rt::thread::Generic& handle);
          const sk::rt::thread::State& getState() const;
          thread::abstract::Thread& getThreadImplementation() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          // sk::rt::Runnable implementation.
          void run();
      
        private:
          Runner(const Runner& other);
          Runner& operator = (const Runner& other);

          sk::rt::Runnable& _target;
          sk::rt::thread::Generic& _generic;
          sk::util::Holder<thread::abstract::Thread> _threadHolder;
          mutable sk::util::Holder<const sk::rt::thread::State> _stateHolder;
          sk::rt::Scope _scope;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_RUNNER_H_ */

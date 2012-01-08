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

#include <sk/rt/thread/platform/Thread.h>
#include <sk/rt/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Runner
        : public virtual sk::rt::Runnable
      {
        public:
          Runner(sk::rt::Runnable& target, sk::rt::thread::Generic& thread);
          virtual ~Runner();

          sk::rt::Scope& getScope();

          void start(sk::rt::thread::Generic& handle);
          void stop();
          void interrupt();
          void detach();

          const sk::rt::thread::State& getState();

          thread::platform::Thread& getThreadImplementation() const;
          int getExitStatus() const;
          bool isInterrupted();
          bool isDetached();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          // sk::rt::Runnable implementation.
          void run();

        private:
          Runner(const Runner& other);
          Runner& operator = (const Runner& other);

          void setState(const thread::State& state);

          sk::rt::Scope _scope;
          sk::rt::Runnable& _target;
          sk::rt::thread::Generic& _generic;
          sk::util::Holder<thread::platform::Thread> _threadHolder;
          sk::util::Holder<sk::rt::thread::State> _stateHolder;
          Mutex _stateMutex;
          int _exitStatus;
          bool _detached;
          volatile bool _interrupted;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_RUNNER_H_ */

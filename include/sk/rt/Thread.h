/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_H_
#define _SK_RT_THREAD_H_

#include <sk/rt/Runnable.h>
#include <sk/rt/thread/State.h>
#include <sk/util/Holder.hxx>

#include <sk/rt/thread/abstract/Thread.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Runner;
    }
    class Thread 
      : public virtual sk::rt::Runnable
    {
      public:
        Thread();
        Thread(const sk::util::String& name);
        Thread(sk::rt::Runnable& target);
        Thread(sk::rt::Runnable& target, const sk::util::String& name);
        Thread(sk::rt::Runnable* target);
        Thread(sk::rt::Runnable* target, const sk::util::String& name);
        virtual ~Thread();

        void start();
        void stop();
        void join();
        void interrupt();

        const sk::util::String getName() const;
        const sk::rt::thread::State& getState() const;

        bool isAlive() const;
        bool isInterrupted() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        long long getId() const;

        static Thread& currentThread();
        static int activeCount();
        static void yield();
        static void pass();

        static void setup();
        static void reset();

      protected:
        virtual void run() const;
    
      private:
        Thread(const Thread& other);
        Thread& operator = (const Thread& other);

        void init();

        sk::util::Holder<sk::rt::Runnable> _targetHolder;
        sk::util::Holder<thread::Runner> _runnerHolder;
        sk::util::Holder<thread::abstract::Thread> _threadHolder;

        sk::util::String _name;
        long long _id;
    };
  }
}

#endif /* _SK_RT_THREAD_H_ */

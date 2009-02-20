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
#include <sk/util/String.h>

#include <sk/rt/thread/Generic.h>
#include <sk/rt/thread/UncaughtExceptionHandler.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Runner;
    }

    class Thread 
      : public virtual sk::rt::thread::Generic,
        public virtual sk::rt::Runnable
    {
      public:
        Thread();
        Thread(const sk::util::String& name);
        Thread(sk::rt::Runnable& target);
        Thread(sk::rt::Runnable& target, const sk::util::String& name);
        Thread(sk::rt::Runnable* target);
        Thread(sk::rt::Runnable* target, const sk::util::String& name);
        virtual ~Thread();

        // sk::rt::thread::Generic implementation
        void start();
        void stop();
        void join();
        void interrupt();

        // sk::rt::thread::Generic implementation
        const sk::util::String getName() const;
        const sk::rt::thread::State& getState() const;

        // sk::rt::thread::Generic implementation
        bool isAlive() const;
        bool isInterrupted() const;
        bool isMain() const;
        bool isService() const;
        bool isRegular() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        uint64_t getId() const;

        static thread::Generic& currentThread();
        static int activeCount();
        static void yield();
        static void pass();
        static void sleep(uint64_t milliseconds);

        static void setDefaultUncaughtExceptionHandler(thread::UncaughtExceptionHandler& handler);
        static thread::UncaughtExceptionHandler& getDefaultUncaughtExceptionHandler(); 

        static void reset();

      protected:
        virtual void run() const;
    
      private:
        Thread(const Thread& other);
        Thread& operator = (const Thread& other);

        void init();

        sk::util::Holder<sk::rt::Runnable> _targetHolder;
        sk::util::Holder<thread::Runner> _runnerHolder;

        sk::util::String _name;
        uint64_t _id;
    };
  }
}

#endif /* _SK_RT_THREAD_H_ */

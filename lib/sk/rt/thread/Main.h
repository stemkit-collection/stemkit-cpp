/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_MAIN_H_
#define _SK_RT_THREAD_MAIN_H_

#include <sk/util/Holder.hxx>
#include <sk/rt/thread/Generic.h>
#include <sk/rt/thread/platform/Thread.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Main 
        : public virtual sk::rt::thread::Generic
      {
        public:
          Main();
          virtual ~Main();
      
          // sk::rt::thread::Generic implementation
          void start(int stackSize = 0);
          void stop();
          void join();
          void detach();
          void interrupt();

          // sk::rt::thread::Generic implementation
          const sk::util::String getName() const;
          const sk::rt::thread::State& getState() const;

          // sk::rt::thread::Generic implementation
          bool isAlive() const;
          bool isInterrupted() const;
          bool isException() const;
          bool isExited() const;
          int exitStatus() const;

          // sk::rt::thread::Generic implementation
          bool isMain() const;
          bool isService() const;
          bool isRegular() const;
          bool isDetached() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
          uint64_t getId() const;
      
        private:
          Main(const Main& other);
          Main& operator = (const Main& other);

          sk::util::Holder<platform::Thread> _threadHolder;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_MAIN_H_ */

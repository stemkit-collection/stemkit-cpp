/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_MOCK_IMPLEMENTATION_H_
#define _SK_RT_THREAD_MOCK_IMPLEMENTATION_H_

#include <sk/rt/thread/platform/Implementation.h>
#include <sk/rt/thread/platform/ConditionMediator.h>
#include "Mutex.h"
#include "Thread.h"

namespace sk {
  namespace rt {
    namespace thread {
      namespace mock {
        class Implementation 
          : public virtual sk::rt::thread::platform::Implementation
        {
          public:
            Implementation();
            virtual ~Implementation();

            // sk::rt::thread::platform::Implementation implementation.
            platform::ConditionMediator* makeConditionMediator(sk::rt::Lock& lock, int capacity) const;
            platform::Mutex* makeSimpleMutex() const;
            platform::Mutex* makeRecursiveMutex() const;
            platform::Thread* makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const;
            platform::Thread* wrapCurrentThread(sk::rt::thread::Generic& handle) const;
            sk::rt::thread::Generic& getGeneric() const;
            void sleep(uint64_t milliseconds) const;
            void yield() const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Implementation(const Implementation& other);
            Implementation& operator = (const Implementation& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_MOCK_IMPLEMENTATION_H_ */

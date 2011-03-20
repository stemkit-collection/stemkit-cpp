/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_IMPLEMENTATION_H_
#define _SK_RT_THREAD_PTHREADS_IMPLEMENTATION_H_

#include <sk/rt/thread/platform/Implementation.h>
#include <sk/rt/Scope.h>

#include "Mutex.h"
#include "Thread.h"
#include "Provider.h"

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Implementation 
          : public virtual sk::rt::thread::platform::Implementation,
            public virtual Provider
        {
          public:
            Implementation();
            virtual ~Implementation();

            // sk::rt::thread::platform::Implementation implmentation.
            platform::ConditionMediator* makeConditionMediator(sk::rt::Lock& lockk, int capacity) const;
            pthreads::Mutex* makeSimpleMutex() const;
            pthreads::Mutex* makeRecursiveMutex() const;
            pthreads::Thread* makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const;
            pthreads::Thread* wrapCurrentThread(sk::rt::thread::Generic& handle) const;
            sk::rt::thread::Generic& getGeneric() const;
            void sleep(uint64_t milliseconds) const;
            void yield() const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Implementation(const Implementation& other);
            Implementation& operator = (const Implementation& other);

            // sk::rt::thread::pthread::Provider implementation.
            void installGeneric(sk::rt::thread::Generic& handle) const;
            void clearGeneric() const;

            void cleanup();

            sk::rt::Scope _scope;
            pthread_key_t _currentThreadKey;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_IMPLEMENTATION_H_ */

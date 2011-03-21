/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_PTHREADS_MUTEX_H_
#define _SK_RT_THREAD_PTHREADS_MUTEX_H_

#include <sk/rt/thread/platform/Mutex.h>
#include <sk/rt/Scope.h>
#include <pthread.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Mutex 
          : public virtual sk::rt::thread::platform::Mutex
        {
          public:
            virtual ~Mutex();

            pthread_mutex_t& getHandle();

            // sk::rt::thread::platform::Mutex implementation
            void lock();
            void unlock();
            bool tryLock();
            void reset();
            bool hasEnterCount() const;
            int getEnterCount() const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;

            static Mutex* makeRecursive();
            static Mutex* makeSingular();
        
          private:
            Mutex(int mutex_type, const sk::rt::Scope scope);
            Mutex(const Mutex& other);
            Mutex& operator = (const Mutex& other);

            void destroyMutex();
            void destroyMutexAttributes();

            sk::rt::Scope _scope;
            pthread_mutex_t _mutex;
            pthread_mutexattr_t _attributes;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_MUTEX_H_ */

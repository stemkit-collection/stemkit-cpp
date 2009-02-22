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

#include <sk/rt/thread/abstract/Mutex.h>
#include <sk/rt/Scope.h>
#include <pthread.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Mutex 
          : public virtual sk::rt::thread::abstract::Mutex
        {
          public:
            virtual ~Mutex();

            // sk::rt::thread::abstract::Mutex implementation
            void lock();
            void unlock();
            bool tryLock();
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

            pthread_mutex_t _mutex;
            pthread_mutexattr_t _attributes;
            sk::rt::Scope _scope;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_MUTEX_H_ */

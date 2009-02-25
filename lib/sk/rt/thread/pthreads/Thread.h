/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_PTHREADS_THREAD_H_
#define _SK_RT_THREAD_PTHREADS_THREAD_H_

#include <sk/rt/thread/abstract/Thread.h>
#include <sk/rt/thread/Generic.h>
#include <sk/rt/Scope.h>
#include <sk/rt/Runnable.h>
#include <pthread.h>

#include "Provider.h"

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Thread 
          : public virtual sk::rt::thread::abstract::Thread
        {
          public:
            Thread(const Provider& provider, sk::rt::thread::Generic& handle);
            Thread(const Provider& provider, sk::rt::Runnable& target, thread::Generic& handle);
            virtual ~Thread();

            // sk::rt::thread::abstract::Thread implementation.
            void start();
            void stop();
            void interrupt();
            void join();
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Thread(const Thread& other);
            Thread& operator = (const Thread& other);

            void run();
            static void* runner(void* data);

            sk::rt::Scope _scope;
            pthread_t _thread;
            sk::rt::Runnable& _target;
            sk::rt::thread::Generic& _handle;
            const Provider& _provider;
            bool _wrapper;
            bool _stopping;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_THREAD_H_ */

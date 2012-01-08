/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_CONDITION_H_
#define _SK_RT_THREAD_PTHREADS_CONDITION_H_

#include <sk/util/Object.h>
#include "Mutex.h"

#include <pthread.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Condition
          : public virtual sk::util::Object
        {
          public:
            Condition(const sk::rt::Scope& scope, pthreads::Mutex& mutex);
            virtual ~Condition();

            pthread_cond_t& getHandle();

            void wait();
            void waitUntil(const struct timespec& moment);
            void broadcast();
            void signal();

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;

          private:
            Condition(const Condition& other);
            Condition& operator = (const Condition& other);

            void cleanup();

            pthread_mutex_t& _mutexHandle;
            pthread_cond_t _conditionHandle;
            const sk::rt::Scope& _scope;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_CONDITION_H_ */

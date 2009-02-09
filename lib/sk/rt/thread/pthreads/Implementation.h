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

#include <sk/rt/thread/abstract/Implementation.h>
#include "Mutex.h"
#include "Thread.h"

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Implementation 
          : public virtual sk::rt::thread::abstract::Implementation
        {
          public:
            Implementation();
            virtual ~Implementation();

            pthreads::Mutex* makeMutex() const;
            pthreads::Thread* makeThread(sk::rt::Runnable& target) const;
            pthreads::Thread* wrapCurrentThread() const;
        
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

#endif /* _SK_RT_THREAD_PTHREADS_IMPLEMENTATION_H_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_ABSTRACT_IMPLEMENTATION_H_
#define _SK_RT_THREAD_ABSTRACT_IMPLEMENTATION_H_

#include <sk/util/Object.h>
#include <sk/rt/thread/abstract/Mutex.h>
#include <sk/rt/thread/abstract/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/thread/Generic.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace abstract {
        class Implementation 
          : public virtual sk::util::Object
        {
          public:
            virtual abstract::Mutex* makeSimpleMutex() const = 0;
            virtual abstract::Mutex* makeRecursiveMutex() const = 0;
            virtual abstract::Thread* makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const = 0;
            virtual abstract::Thread* wrapCurrentThread(sk::rt::thread::Generic& handle) const = 0;
            virtual sk::rt::thread::Generic& getGeneric() const = 0;
            virtual void sleep(uint64_t milliseconds) const = 0;
            virtual void yield() const = 0;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_ABSTRACT_IMPLEMENTATION_H_ */

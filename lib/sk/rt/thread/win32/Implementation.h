/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_WIN32_IMPLEMENTATION_H_
#define _SK_RT_THREAD_WIN32_IMPLEMENTATION_H_

#include <sk/rt/thread/abstract/Implementation.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace win32 {
        class Implementation 
          : public virtual sk::rt::thread::abstract::Implementation
        {
          public:
            Implementation();
            virtual ~Implementation();
        
            // sk::rt::thread::abstract::Implementation implementation.
            abstract::Mutex* makeSimpleMutex() const;
            abstract::Mutex* makeRecursiveMutex() const;
            abstract::Thread* makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const;
            abstract::Thread* wrapCurrentThread(sk::rt::thread::Generic& handle) const;
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

#endif /* _SK_RT_THREAD_WIN32_IMPLEMENTATION_H_ */

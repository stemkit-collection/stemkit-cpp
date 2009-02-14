/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_MOCK_MUTEX_H_
#define _SK_RT_THREAD_MOCK_MUTEX_H_

#include <sk/rt/thread/abstract/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace mock {
        class Mutex 
          : public virtual sk::rt::thread::abstract::Mutex
        {
          public:
            Mutex();
            virtual ~Mutex();

            void lock();
            void unlock();
            bool tryLock();

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Mutex(const Mutex& other);
            Mutex& operator = (const Mutex& other);

            bool _locked;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_MOCK_MUTEX_H_ */
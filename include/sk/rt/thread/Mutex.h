/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_MUTEX_H_
#define _SK_RT_THREAD_MUTEX_H_

#include <sk/rt/Runnable.h>
#include <sk/rt/Lockable.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Mutex 
        : public virtual sk::rt::Lockable
      {
        public:
          Mutex();
          virtual ~Mutex();

          bool isLocked() const;
          bool isOwner() const;
      
          // sk::rt::Locable implementation.
          void lock();
          void unlock();
          void synchronize(const sk::rt::Runnable& block);

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

#endif /* _SK_RT_THREAD_MUTEX_H_ */

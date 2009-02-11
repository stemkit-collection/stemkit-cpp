/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_ABSTRACTLOCK_H_
#define _SK_RT_THREAD_ABSTRACTLOCK_H_

#include <sk/util/Holder.hxx>

#include <sk/rt/Runnable.h>
#include <sk/rt/Lockable.h>
#include <sk/rt/thread/abstract/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      class AbstractLock 
        : public virtual sk::rt::Lockable
      {
        public:
          virtual ~AbstractLock();

          virtual bool isLocked() const = 0;
      
          // sk::rt::Locable implementation.
          void lock();
          bool tryLock();
          void unlock();
          void synchronize(const sk::rt::Runnable& block);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        protected:
          AbstractLock(abstract::Mutex* mutex);

          bool tryLockCheck() const;
          virtual const sk::util::String collectInspectInfo() const;

        private:
          AbstractLock(const AbstractLock& other);
          AbstractLock& operator = (const AbstractLock& other);

          sk::util::Holder<abstract::Mutex> _mutexHolder;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_ABSTRACTLOCK_H_ */

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

#include <ostream>

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

          using Lockable::synchronize;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;

        protected:
          AbstractLock(abstract::Mutex* mutex, bool ownership);

          bool tryLockCheck() const;
          virtual void collectInspectInfo(std::ostream& stream) const;

        private:
          AbstractLock(const AbstractLock& other);
          AbstractLock& operator = (const AbstractLock& other);

          void registerOwnership();

          sk::util::Holder<abstract::Mutex> _mutexHolder;
          uint64_t _lastOwner;
          bool _ownership;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_ABSTRACTLOCK_H_ */

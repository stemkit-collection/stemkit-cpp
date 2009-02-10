/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_REENTRANTLOCK_H_
#define _SK_RT_THREAD_REENTRANTLOCK_H_

#include <sk/util/Holder.hxx>

#include <sk/rt/Runnable.h>
#include <sk/rt/Lockable.h>
#include <sk/rt/thread/abstract/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Generic;

      class ReentrantLock 
        : public virtual sk::rt::Lockable
      {
        public:
          ReentrantLock();
          virtual ~ReentrantLock();

          bool isLocked() const;
          int getHoldCount() const;
      
          // sk::rt::Locable implementation.
          void lock();
          bool tryLock();
          void unlock();
          void synchronize(const sk::rt::Runnable& block);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        private:
          ReentrantLock(const ReentrantLock& other);
          ReentrantLock& operator = (const ReentrantLock& other);

          void processLocked();
          void processUnlocked();

          int _holdCount;
          sk::util::Holder<abstract::Mutex> _mutexHolder;
          sk::util::Holder<sk::rt::thread::Generic> _ownerHolder;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_REENTRANTLOCK_H_ */

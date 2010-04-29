/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_REENTRANTLOCK_H_
#define _SK_RT_REENTRANTLOCK_H_

#include <sk/rt/thread/AbstractLock.h>

namespace sk {
  namespace rt {
    class ReentrantLock 
      : public thread::AbstractLock
    {
      public:
        ReentrantLock();
        virtual ~ReentrantLock();

        bool isLocked() const;
        int getCounter() const;
    
        // sk::rt::thread::AbstractLock re-implementation.
        void lock();
        bool tryLock();
        void unlock();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        void collectInspectInfo(std::ostream& stream) const;
    
      private:
        ReentrantLock(const ReentrantLock& other);
        ReentrantLock& operator = (const ReentrantLock& other);

        void processLocked();

        int _counter;
    };
  }
}

#endif /* _SK_RT_REENTRANTLOCK_H_ */

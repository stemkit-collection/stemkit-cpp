/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_REENTRANTREADWRITELOCK_H_
#define _SK_RT_REENTRANTREADWRITELOCK_H_

#include <sk/rt/ReadWriteLock.h>

namespace sk {
  namespace rt {
    class ReentrantReadWriteLock
      : public virtual sk::rt::ReadWriteLock
    {
      public:
        ReentrantReadWriteLock();
        virtual ~ReentrantReadWriteLock();

        // sk::rt::ReadWriteLock implementation.
        sk::rt::Lock& readLock();
        sk::rt::Lock& writeLock();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        ReentrantReadWriteLock(const ReentrantReadWriteLock& other);
        ReentrantReadWriteLock& operator = (const ReentrantReadWriteLock& other);
    };
  }
}

#endif /* _SK_RT_REENTRANTREADWRITELOCK_H_ */

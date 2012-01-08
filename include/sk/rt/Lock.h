/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOCK_H_
#define _SK_RT_LOCK_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    class Lock
      : public virtual sk::util::Object
    {
      public:
        virtual void lock() = 0;
        virtual bool tryLock() = 0;
        virtual void unlock() = 0;
        virtual void reset() = 0;
        virtual bool isLocked() const = 0;
    };
  }
}

#endif /* _SK_RT_LOCK_H_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_READWRITELOCK_H_
#define _SK_RT_READWRITELOCK_H_

#include <sk/util/Object.h>
#include <sk/rt/Lock.h>

namespace sk {
  namespace rt {
    class ReadWriteLock 
      : public virtual sk::util::Object
    {
      public:
        virtual sk::rt::Lock& readLock() = 0;
        virtual sk::rt::Lock& writeLock() = 0;
    };
  }
}

#endif /* _SK_RT_READWRITELOCK_H_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_MUTEX_H_
#define _SK_RT_MUTEX_H_

#include <sk/rt/thread/AbstractLock.h>

namespace sk {
  namespace rt {
    class Mutex 
      : public thread::AbstractLock
    {
      public:
        Mutex();
        Mutex(bool ownership);
        virtual ~Mutex();

        bool isLocked() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Mutex(const Mutex& other);
        Mutex& operator = (const Mutex& other);
    };
  }
}

#endif /* _SK_RT_MUTEX_H_ */

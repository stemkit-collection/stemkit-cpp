/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_SCOPEARBITRATOR_H_
#define _SK_RT_THREAD_SCOPEARBITRATOR_H_

#include <sk/rt/scope/Arbitrator.h>
#include <sk/rt/ReentrantLock.h>

namespace sk {
  namespace rt {
    namespace thread {
      class ScopeArbitrator 
        : public virtual sk::rt::scope::Arbitrator
      {
        public:
          ScopeArbitrator();
          virtual ~ScopeArbitrator();
      
          // sk::rt::scope::Arbitrator implementation.
          void lock();
          void unlock();
          uint64_t currentThreadId() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ScopeArbitrator(const ScopeArbitrator& other);
          ScopeArbitrator& operator = (const ScopeArbitrator& other);

          sk::rt::ReentrantLock _mutex;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_SCOPEARBITRATOR_H_ */

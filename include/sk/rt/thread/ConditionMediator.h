/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_CONDITIONMEDIATOR_H_
#define _SK_RT_THREAD_CONDITIONMEDIATOR_H_

#include <sk/util/Object.h>
#include <sk/rt/Lock.h>
#include <sk/rt/thread/Condition.h>
#include <sk/rt/thread/Conditional.h>

namespace sk {
  namespace rt {
    namespace thread {
      class ConditionMediator 
        : public virtual sk::rt::thread::Condition
      {
        public:
          ConditionMediator(sk::rt::Lock& lock);
          virtual ~ConditionMediator();

          void synchronize(sk::rt::thread::Conditional& block);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ConditionMediator(const ConditionMediator& other);
          ConditionMediator& operator = (const ConditionMediator& other);

          // sk::rt::thread::Condition implementation.
          void ensure(bool expression, int timeout);
          void announce();

          void lock();
          void unlock();
          void ensureLockOwner();

          sk::rt::Lock& _lock;
          uint64_t _lockOwnerId;
          bool _locked;

          struct WaitRequest;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_CONDITIONMEDIATOR_H_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_GENERIC_CONDITIONMEDIATOR_H_
#define _SK_RT_THREAD_GENERIC_CONDITIONMEDIATOR_H_

#include <sk/util/Object.h>
#include <sk/rt/Lock.h>
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Condition.h>
#include <sk/rt/thread/Conditional.h>
#include <sk/rt/thread/platform/ConditionMediator.h>
#include <sk/rt/Mutex.h>

#include <sk/util/ArrayList.hxx>
#include <sk/util/Vector.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      namespace generic {
        class ConditionMediator 
          : public virtual sk::rt::thread::platform::ConditionMediator,
            public virtual sk::rt::thread::Condition
        {
          public:
            ConditionMediator(sk::rt::Lock& lock, int capacity = 1);
            virtual ~ConditionMediator();

            void invoke(const sk::rt::thread::Conditional& block);

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            ConditionMediator(const ConditionMediator& other);
            ConditionMediator& operator = (const ConditionMediator& other);

            // sk::rt::thread::Condition implementation.
            void ensure(bool expression, uint64_t timeout);
            void ensure(int channel, bool expression, uint64_t timeout);
            void announce(bool expression);
            void announce(int channel, bool expression);

            sk::rt::Lock& _lock;
            typedef sk::util::ArrayList<sk::rt::thread::Generic> thread_container_t;
            sk::util::Vector<thread_container_t>::Direct _waiters;
            sk::rt::Mutex _mutex;

            struct WaitRequest;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_GENERIC_CONDITIONMEDIATOR_H_ */

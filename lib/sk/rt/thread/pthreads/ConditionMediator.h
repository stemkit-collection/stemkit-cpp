/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_PTHREADS_CONDITIONMEDIATOR_H_
#define _SK_RT_THREAD_PTHREADS_CONDITIONMEDIATOR_H_

#include <sk/rt/Lock.h>
#include <sk/rt/thread/Conditional.h>
#include <sk/rt/thread/platform/ConditionMediator.h>
#include <sk/rt/Scope.h>

#include <sk/util/Vector.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Condition;

        class ConditionMediator 
          : public virtual sk::rt::thread::platform::ConditionMediator
        {
          public:
            ConditionMediator(const sk::rt::Scope& scope, sk::rt::Lock& lock, int capacity = 1);
            virtual ~ConditionMediator();

            void invoke(const sk::rt::thread::Conditional& block);
            void wait(int channel, uint64_t timeout);
            void announce(int channel);

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            ConditionMediator(const ConditionMediator& other);
            ConditionMediator& operator = (const ConditionMediator& other);

            sk::rt::Lock& _lock;
            sk::util::Vector<pthreads::Condition>::Direct _conditions;
            const sk::rt::Scope& _scope;

            struct WaitRequest;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_CONDITIONMEDIATOR_H_ */

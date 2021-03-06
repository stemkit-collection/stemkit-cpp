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

#include <sk/rt/Lock.h>
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Conditional.h>
#include <sk/rt/thread/platform/ConditionMediator.h>
#include <sk/rt/Mutex.h>
#include <sk/rt/Scope.h>
#include <sk/rt/Time.h>

#include <sk/util/ArrayList.hxx>
#include <sk/util/Vector.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      namespace generic {
        class ConditionMediator
          : public virtual sk::rt::thread::platform::ConditionMediator
        {
          public:
            ConditionMediator(const sk::rt::Scope& scope, sk::rt::Lock& lock, int capacity = 1);
            virtual ~ConditionMediator();

            bool invoke(bool blocking, const sk::rt::thread::Conditional& block);
            void wait(int channel);
            void wait(int channel, const sk::rt::Time& moment);
            void announce(int channel);

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;

          private:
            ConditionMediator(const ConditionMediator& other);
            ConditionMediator& operator = (const ConditionMediator& other);

            sk::rt::Lock& _lock;
            typedef sk::util::ArrayList<thread::Generic> thread_container_t;
            sk::util::Vector<thread_container_t>::Direct _waiters;
            sk::rt::Mutex _mutex;
            const sk::rt::Scope& _scope;
            const int _delay;
            const bool _yields;
            const bool _broadcasts;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_GENERIC_CONDITIONMEDIATOR_H_ */

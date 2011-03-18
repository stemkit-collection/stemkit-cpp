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
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Condition.h>
#include <sk/rt/thread/Conditional.h>
#include <sk/rt/Mutex.h>

#include <sk/util/ArrayList.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      class ConditionMediator 
        : public virtual sk::rt::thread::Condition
      {
        public:
          ConditionMediator(sk::rt::Lock& lock);
          virtual ~ConditionMediator();

          template<typename T>
          void synchronize(T& block);

          template<typename T, typename TMF> 
          void synchronize(T& target, TMF method);
      
          template<typename T, typename TMF, typename P> 
          void synchronize(T& target, TMF method, P param);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ConditionMediator(const ConditionMediator& other);
          ConditionMediator& operator = (const ConditionMediator& other);

          // sk::rt::thread::Condition implementation.
          void ensure(bool expression, uint64_t timeout);
          void announce(bool expression);

          void invoke(const sk::rt::thread::Conditional& block);

          sk::rt::Lock& _lock;
          sk::util::ArrayList<sk::rt::thread::Generic> _waiters;
          sk::rt::Mutex _mutex;

          struct WaitRequest;

          template<typename T, typename TMF> 
          struct MemberFunctionInvocator;

          template<typename T, typename TMF, typename P> 
          struct MemberFunctionWithParamInvocator;
      };
    }
  }
}

template<typename T>
void
sk::rt::thread::ConditionMediator::
synchronize(T& block)
{
  invoke(block);
}

template<typename T, typename TMF>
struct sk::rt::thread::ConditionMediator::MemberFunctionInvocator : public virtual sk::rt::thread::Conditional {
  MemberFunctionInvocator(T& target, TMF method)
    : _target(target), _method(method) {}

  void process(sk::rt::thread::Condition& condition) const {
    (_target.*_method)(condition);
  }
  T& _target;
  TMF _method;
};

template<typename T, typename TMF>
void
sk::rt::thread::ConditionMediator::
synchronize(T& target, TMF method)
{
  invoke(MemberFunctionInvocator<T, TMF>(target, method));
}

template<typename T, typename TMF, typename P>
struct sk::rt::thread::ConditionMediator::MemberFunctionWithParamInvocator : public virtual sk::rt::thread::Conditional {
  MemberFunctionWithParamInvocator(T& target, TMF method, P param)
    : _target(target), _method(method), _param(param) {}

  void process(sk::rt::thread::Condition& condition) const {
    (_target.*_method)(condition, _param);
  }
  T& _target;
  TMF _method;
  P _param;
};

template<typename T, typename TMF, typename P>
void
sk::rt::thread::ConditionMediator::
synchronize(T& target, TMF method, P param)
{
  invoke(MemberFunctionWithParamInvocator<T, TMF, P>(target, method, param));
}

#endif /* _SK_RT_THREAD_CONDITIONMEDIATOR_H_ */

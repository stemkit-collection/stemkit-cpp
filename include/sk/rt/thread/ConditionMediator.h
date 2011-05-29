/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
*  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (bystr@mac.com)
*/

#ifndef _SK_RT_THREAD_CONDITIONMEDIATOR_H_
#define _SK_RT_THREAD_CONDITIONMEDIATOR_H_

#include <sk/rt/Lock.h>
#include <sk/rt/thread/Condition.h>
#include <sk/rt/thread/Conditional.h>
#include <sk/rt/thread/MethodConditional.hxx>
#include <sk/rt/thread/FunctorConditional.hxx>
#include <sk/rt/thread/platform/ConditionMediator.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      class ConditionMediator 
        : public virtual sk::util::Object
      {
        public:
          ConditionMediator(sk::rt::Lock& lock, int capacity = 1);
          virtual ~ConditionMediator();

          void setBlocking(bool state);
          bool isBlocking() const;

          bool sync(const sk::rt::thread::Conditional& block);

          template<typename T, typename TMF> 
          bool syncMethod(T& target, TMF method);
      
          template<typename T, typename TMF, typename P> 
          bool syncMethod(T& target, TMF method, P& param);
      
          template<typename T, typename TMF, typename P> 
          bool syncMethod(T& target, TMF method, const P& param);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::Object& getObject() const;
          sk::util::Object& getObject();
      
        private:
          ConditionMediator(const ConditionMediator& other);
          ConditionMediator& operator = (const ConditionMediator& other);

          const sk::util::Holder<platform::ConditionMediator>::Direct _mediatorHolder;
          bool _blocking;

          template<typename T, typename TMF> 
          struct MemberFunctionInvocator;

          template<typename T, typename TMF, typename P> 
          struct MemberFunctionWithParamInvocator;
      };
    }
  }
}

template<typename T, typename TMF>
bool
sk::rt::thread::ConditionMediator::
syncMethod(T& target, TMF method)
{
  return sync(sk::rt::thread::MethodConditional<T, TMF>(target, method));
}

template<typename T, typename TMF, typename P>
bool
sk::rt::thread::ConditionMediator::
syncMethod(T& target, TMF method, P& param)
{
  return sync(sk::rt::thread::MethodConditional<T, TMF, P&>(target, method, param));
}

template<typename T, typename TMF, typename P>
bool
sk::rt::thread::ConditionMediator::
syncMethod(T& target, TMF method, const P& param)
{
  return sync(sk::rt::thread::MethodConditional<T, TMF, const P&>(target, method, param));
}

#endif /* _SK_RT_THREAD_CONDITIONMEDIATOR_H_ */

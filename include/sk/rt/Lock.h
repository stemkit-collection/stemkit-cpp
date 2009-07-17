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

        template<typename R, typename T, typename TMF> 
        R synchronize(T& target, TMF method);

        template<typename T, typename TMF> 
        void synchronize(T& target, TMF method);

        template<typename T, typename TMF, typename P> 
        void synchronize(T& target, TMF method, P& param);

        template<typename T> 
        void synchronize(T& target);

        template<typename T> 
        void synchronize(const T& target);

        template<typename T, typename TMF, typename P> 
        struct MemberFunctionWithParamInvocator;
    };

    typedef void (function_t)();
    template<> void Lock::synchronize<function_t>(function_t& function);
  }
}

template<typename R, typename T, typename TMF>
R
sk::rt::Lock::
synchronize(T& target, TMF method)
{
  lock();

  try {
    R result = (target.*method)();
    unlock();
    return result;
  }
  catch(...) {
    unlock();
    throw;
  }
}

template<typename T, typename TMF>
void
sk::rt::Lock::
synchronize(T& target, TMF method)
{
  lock();

  try {
    (target.*method)();
  }
  catch(...) {
    unlock();
    throw;
  }
  unlock();
}

// The following implementation almost duplicates the one above. While 
// violating DRY principle, it provides the fastest implementation, so
// until better solution comes up, let's keep it this way (following
// commented out block demonstrates possible DRY-ing, however for the
// price of intermediate class instantiation with data copy).
//
template<typename T, typename TMF, typename P>
void
sk::rt::Lock::
synchronize(T& target, TMF method, P& param)
{
  lock();

  try {
    (target.*method)(param);
  }
  catch(...) {
    unlock();
    throw;
  }
  unlock();
}

#if 0 

template<typename T, typename TMF, typename P>
struct sk::rt::Lock::MemberFunctionWithParamInvocator {
  MemberFunctionWithParamInvocator(T& target, TMF method, P& param)
    : _target(target), _method(method), _param(param) {}

  void invoke() {
    (_target.*_method)(_param);
  }
  T& _target;
  TMF _method;
  P& _param;
};

template<typename T, typename TMF, typename P>
void
sk::rt::Lock::
synchronize(T& target, TMF method, P& param)
{
  MemberFunctionWithParamInvocator<T, TMF, P> invocator(target, method, param);
  synchronize(invocator, &MemberFunctionWithParamInvocator<T, TMF, P>::invoke);
}

#endif

template<typename T>
void 
sk::rt::Lock::
synchronize(T& target)
{
  synchronize(target, &T::operator());
}

template<typename T>
void 
sk::rt::Lock::
synchronize(const T& target)
{
  synchronize(target, &T::operator());
}

#endif /* _SK_RT_LOCK_H_ */

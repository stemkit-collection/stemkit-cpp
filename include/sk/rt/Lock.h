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
        virtual bool isLocked() const = 0;

        template<typename T, typename P>
        struct ptr {
          typedef void (T::*member_function_t)(P& param);
          typedef void (T::*const_member_function_t)(P& param) const;
        };
        typedef void (function_t)();

        template<typename T> void synchronize(T& target, typename ptr<T, void>::member_function_t method);
        template<typename T> void synchronize(const T& target, typename ptr<T, void>::const_member_function_t method);
        template<typename T> void synchronize(T& target);
        template<typename T> void synchronize(const T& target);

        template<typename T, typename P> void synchronize(T& target, typename ptr<T, P>::member_function_t method, P& param);
        template<typename T, typename P> void synchronize(const T& target, typename ptr<T, P>::const_member_function_t method, P& param);

        template<typename T> struct ConstMemberFunctionInvocator;
        template<typename T, typename P> struct MemberFunctionWithParamInvocator;
        template<typename T, typename P> struct ConstMemberFunctionWithParamInvocator;
    };

    template<typename T>
    struct Lock::ptr<T, void> {
      typedef void (T::*member_function_t)();
      typedef void (T::*const_member_function_t)() const;
    };

    template<>
    struct Lock::ptr<Lock::function_t, void> {
    };

    template<> void Lock::synchronize<Lock::function_t>(Lock::function_t& function);
  }
}

template<typename T>
void
sk::rt::Lock::
synchronize(T& target, typename ptr<T, void>::member_function_t method)
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

template<typename T>
struct sk::rt::Lock::ConstMemberFunctionInvocator {
  ConstMemberFunctionInvocator(const T& target, typename ptr<T, void>::const_member_function_t method)
    : _target(target), _method(method) {}

  void invoke() {
    (_target.*_method)();
  }
  const T& _target;
  typename ptr<T, void>::const_member_function_t _method;
};

template<typename T>
void
sk::rt::Lock::
synchronize(const T& target, typename ptr<T, void>::const_member_function_t method)
{
  ConstMemberFunctionInvocator<T> invocator(target, method);
  synchronize(invocator, &ConstMemberFunctionInvocator<T>::invoke);
}

template<typename T, typename P>
struct sk::rt::Lock::MemberFunctionWithParamInvocator {
  MemberFunctionWithParamInvocator(T& target, typename ptr<T, P>::member_function_t method, P& param)
    : _target(target), _method(method), _param(param) {}

  void invoke() {
    (_target.*_method)(_param);
  }
  T& _target;
  typename ptr<T, P>::member_function_t _method;
  P& _param;
};

template<typename T, typename P>
void
sk::rt::Lock::
synchronize(T& target, typename ptr<T, P>::member_function_t method, P& param)
{
  MemberFunctionWithParamInvocator<T, P> invocator(target, method, param);
  synchronize(invocator, &MemberFunctionWithParamInvocator<T, P>::invoke);
}

template<typename T, typename P>
struct sk::rt::Lock::ConstMemberFunctionWithParamInvocator {
  ConstMemberFunctionWithParamInvocator(const T& target, typename ptr<T, P>::const_member_function_t method, P& param)
    : _target(target), _method(method), _param(param) {}

  void invoke() {
    (_target.*_method)(_param);
  }
  const T& _target;
  typename ptr<T, P>::const_member_function_t _method;
  P& _param;
};

template<typename T, typename P>
void
sk::rt::Lock::
synchronize(const T& target, typename ptr<T, P>::const_member_function_t method, P& param)
{
  ConstMemberFunctionWithParamInvocator<T, P> invocator(target, method, param);
  synchronize(invocator, &ConstMemberFunctionWithParamInvocator<T, P>::invoke);
}

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

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
#include <sk/rt/Runnable.h>

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

        virtual void synchronize(const sk::rt::Runnable& block) = 0;

        template<typename T>
        void synchronize(T& target, void (T::*method)());

        template<typename T, typename P>
        void synchronize(T& target, void (T::*method)(P&), P& param);
    
        /*
        template<typename F>
        void synchronize(const F& functor);
        */

        template<typename T>
        struct ptr {
          typedef void (T::*member_function_t)();
          typedef void (T::*const_member_function_t)() const;
        };

        template<typename T>
        void sync(T& target, typename ptr<T>::member_function_t method);

        template<typename T>
        void sync(const T& target, typename ptr<T>::const_member_function_t method);

        template<typename T>
        void sync(T& target);

        template<typename T>
        void sync(const T& target);
    };
  }
}

template<typename T>
void 
sk::rt::Lock::
synchronize(T& target, void (T::*method)())
{
  struct Block : public virtual sk::rt::Runnable {
    typedef void (T::*member_function_t)();
    Block(T& target, member_function_t method)
      : _target(target), _method(method) {}

    void run() const {
      (_target.*_method)();
    }
    T& _target;
    member_function_t _method;
  };
  synchronize(Block(target, method));
}

template<typename T, typename P>
void 
sk::rt::Lock::
synchronize(T& target, void (T::*method)(P&), P& param)
{
  struct Block : public virtual sk::rt::Runnable {
    typedef void (T::*member_function_t)(P&);
    Block(T& target, member_function_t method, P& param)
      : _target(target), _method(method), _param(param) {}

    void run() const {
      (_target.*_method)(_param);
    }
    T& _target;
    P& _param;
    member_function_t _method;
  };
  synchronize(Block(target, method, param));
}

/*
template<typename F>
void 
sk::rt::Lock::
synchronize(const F& functor)
{
  struct Block : public virtual sk::rt::Runnable {
    Block(const F& functor)
      : _functor(functor) {}

    void run() const {
      _functor();
    }
    const F& _functor;
  };
  synchronize(Block(functor));
}
*/

template<typename T>
void
sk::rt::Lock::
sync(T& target, typename ptr<T>::member_function_t method)
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
void
sk::rt::Lock::
sync(const T& target, typename ptr<T>::const_member_function_t method)
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
void 
sk::rt::Lock::
sync(T& target)
{
  sync(target, &T::operator());
}

template<typename T>
void 
sk::rt::Lock::
sync(const T& target)
{
  sync(target, &T::operator());
}

#endif /* _SK_RT_LOCK_H_ */

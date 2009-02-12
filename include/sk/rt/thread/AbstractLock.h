/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_ABSTRACTLOCK_H_
#define _SK_RT_THREAD_ABSTRACTLOCK_H_

#include <sk/util/Holder.hxx>

#include <sk/rt/Runnable.h>
#include <sk/rt/Lockable.h>
#include <sk/rt/thread/abstract/Mutex.h>

#include <ostream>

namespace sk {
  namespace rt {
    namespace thread {
      class AbstractLock 
        : public virtual sk::rt::Lockable
      {
        public:
          virtual ~AbstractLock();

          virtual bool isLocked() const = 0;
      
          // sk::rt::Locable implementation.
          void lock();
          bool tryLock();
          void unlock();
          void synchronize(const sk::rt::Runnable& block);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;

          template<typename T>
          void synchronize(T& target, void (T::*method)());

          template<typename T, typename P>
          void synchronize(T& target, void (T::*method)(P&), P& param);
      
          template<typename F>
          void synchronize(const F& functor);
      
        protected:
          AbstractLock(abstract::Mutex* mutex, bool ownership);

          bool tryLockCheck() const;
          virtual void collectInspectInfo(std::ostream& stream) const;

        private:
          AbstractLock(const AbstractLock& other);
          AbstractLock& operator = (const AbstractLock& other);

          void registerOwnership();

          sk::util::Holder<abstract::Mutex> _mutexHolder;
          uint64_t _lastOwner;
          bool _ownership;
      };
    }
  }
}

template<typename T>
void 
sk::rt::thread::AbstractLock::
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
sk::rt::thread::AbstractLock::
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

template<typename F>
void 
sk::rt::thread::AbstractLock::
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

#endif /* _SK_RT_THREAD_ABSTRACTLOCK_H_ */

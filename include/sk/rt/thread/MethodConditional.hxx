/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_METHODCONDITIONAL_HXX_
#define _SK_RT_THREAD_METHODCONDITIONAL_HXX_

#include <sk/rt/thread/Conditional.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      template<typename T, typename TMF, typename P1 = void, typename P2 = void, typename P3 = void>
      class MethodConditional : public virtual sk::rt::thread::Conditional
      {
        public:
          MethodConditional(T& target, const TMF method, P1 p1, P2 p2, P3 p3)
            : _target(target), _callable(method, p1, p2, p3) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.callTarget(_target, condition);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1, P2, P3> _callable;
      };

      template<typename T, typename TMF, typename P1, typename P2>
      class MethodConditional<T, TMF, P1, P2, void>: public virtual sk::rt::thread::Conditional
      {
        public:
          MethodConditional(T& target, const TMF method, P1 p1, P2 p2)
            : _target(target), _callable(method, p1, p2) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.callTarget(_target, condition);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1, P2> _callable;
      };

      template<typename T, typename TMF, typename P1>
      class MethodConditional<T, TMF, P1, void, void>: public virtual sk::rt::thread::Conditional
      {
        public:
          MethodConditional(T& target, const TMF method, P1 p1)
            : _target(target), _callable(method, p1) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.callTarget(_target, condition);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1> _callable;
      };

      template<typename T, typename TMF>
      class MethodConditional<T, TMF, void, void, void>: public virtual sk::rt::thread::Conditional
      {
        public:
          MethodConditional(T& target, const TMF method)
            : _target(target), _callable(method) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.callTarget(_target, condition);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF> _callable;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_METHODCONDITIONAL_HXX_ */

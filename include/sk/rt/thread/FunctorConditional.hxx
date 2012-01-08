/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_FUNCTORCONDITIONAL_HXX_
#define _SK_RT_THREAD_FUNCTORCONDITIONAL_HXX_

#include <sk/rt/thread/Conditional.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace thread {
      template<typename F, typename P1 = void, typename P2 = void, typename P3 = void>
      class FunctorConditional : public virtual sk::rt::thread::Conditional
      {
        public:
          FunctorConditional(F& functor, P1 p1, P2 p2, P3 p3)
            : _callable(functor, p1, p2, p3) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.call(condition);
          }

        private:
          const sk::rt::Callable<F&, P1, P2, P3> _callable;
      };

      template<typename F, typename P1, typename P2>
      class FunctorConditional<F, P1, P2, void> : public virtual sk::rt::thread::Conditional
      {
        public:
          FunctorConditional(F& functor, P1 p1, P2 p2)
            : _callable(functor, p1, p2) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.call(condition);
          }

        private:
          const sk::rt::Callable<F&, P1, P2> _callable;
      };

      template<typename F, typename P1>
      class FunctorConditional<F, P1, void, void> : public virtual sk::rt::thread::Conditional
      {
        public:
          FunctorConditional(F& functor, P1 p1)
            : _callable(functor, p1) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.call(condition);
          }

        private:
          const sk::rt::Callable<F&, P1> _callable;
      };

      template<typename F>
      class FunctorConditional<F, void, void, void> : public virtual sk::rt::thread::Conditional
      {
        public:
          FunctorConditional(F& functor)
            : _callable(functor) {}

          void process(sk::rt::thread::Condition& condition) const {
            _callable.call(condition);
          }

        private:
          const sk::rt::Callable<F&> _callable;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_FUNCTORCONDITIONAL_HXX_ */

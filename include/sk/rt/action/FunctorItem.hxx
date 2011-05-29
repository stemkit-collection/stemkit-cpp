/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTION_FUNCTORITEM_HXX_
#define _SK_RT_ACTION_FUNCTORITEM_HXX_

#include <sk/rt/action/Item.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace action {
      template<typename F, typename P1 = void, typename P2 = void, typename P3 = void>
      class FunctorItem : public virtual sk::rt::action::Item
      {
        public:
          FunctorItem(const sk::util::String& label, const F& functor, P1 p1, P2 p2, P3 p3)
            : Item(label), _callable(functor, p1, p2, p3) {}

          void invoke() const {
            _callable.call();
          }

        private:
          const sk::rt::Callable<F&, P1, P2, P3> _callable;
      };

      template<typename F, typename P1, typename P2>
      class FunctorItem<F, P1, P2, void> : public virtual sk::rt::action::Item
      {
        public:
          FunctorItem(const sk::util::String& label, const F& functor, P1 p1, P2 p2)
            : Item(label), _callable(functor, p1, p2) {}

          void invoke() const {
            _callable.call();
          }

        private:
          const sk::rt::Callable<F&, P1, P2> _callable;
      };

      template<typename F, typename P1>
      class FunctorItem<F, P1, void, void> : public virtual sk::rt::action::Item
      {
        public:
          FunctorItem(const sk::util::String& label, const F& functor, P1 p1)
            : Item(label), _callable(functor, p1) {}

          void invoke() const {
            _callable.call();
          }

        private:
          const sk::rt::Callable<F&, P1> _callable;
      };

      template<typename F>
      class FunctorItem<F, void, void, void> : public virtual sk::rt::action::Item
      {
        public:
          FunctorItem(const sk::util::String& label, const F& functor)
            : Item(label), _callable(functor) {}

          void invoke() const {
            _callable.call();
          }

        private:
          const sk::rt::Callable<F&> _callable;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_FUNCTORITEM_HXX_ */

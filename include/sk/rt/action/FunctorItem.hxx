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
      template<typename F, typename P1 = void>
      class FunctorItem : public virtual sk::rt::action::Item
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
      class FunctorItem<F, void> : public virtual sk::rt::action::Item
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

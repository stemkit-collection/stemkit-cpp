/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTION_FUNCTOR_HXX_
#define _SK_RT_ACTION_FUNCTOR_HXX_

#include <sk/rt/action/Item.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace action {
      template<typename F, typename P1 = void>
      class Functor : public virtual sk::rt::action::Item
      {
        public:
          Functor(const sk::util::String& label, const F& functor, P1 p1)
            : Item(label), _binder(functor, p1) {}

          void invoke() const {
            _binder.call();
          }

        private:
          const sk::rt::Callable<F&, P1> _binder;
      };

      template<typename F>
      class Functor<F, void> : public virtual sk::rt::action::Item
      {
        public:
          Functor(const sk::util::String& label, const F& functor)
            : Item(label), _binder(functor) {}

          void invoke() const {
            _binder.call();
          }

        private:
          const sk::rt::Callable<F&> _binder;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_FUNCTOR_HXX_ */

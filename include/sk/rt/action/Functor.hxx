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

namespace sk {
  namespace rt {
    namespace action {
      template<typename F, typename P = void>
      class Functor : public virtual sk::rt::action::Item
      {
        public:
          Functor(const sk::util::String& label, const F& functor, P param)
            : Item(label), _functor(functor), _param(param) {}

          Functor(const F& functor, P param)
            : _functor(functor), _param(param) {}

          void invoke() const {
            (_functor)(_param);
          }

        private:
          const F& _functor;
          P _param;
      };

      template<typename F>
      class Functor<F, void> : public virtual sk::rt::action::Item
      {
        public:
          Functor(const sk::util::String& label, const F& functor)
            : Item(label), _functor(functor) {}

          Functor(const F& functor)
            : _functor(functor) {}

          void invoke() const {
            (_functor)();
          }

        private:
          const F& _functor;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_FUNCTOR_HXX_ */

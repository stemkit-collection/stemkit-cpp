/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTION_METHOD_HXX_
#define _SK_RT_ACTION_METHOD_HXX_

#include <sk/rt/action/Item.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace action {
      template<typename T, typename TMF, typename P1 = void>
      class Method : public virtual sk::rt::action::Item
      {
        public:
          Method(const sk::util::String& label, T& target, const TMF method, P1 p1)
            : Item(label), _target(target), _binder(method, p1) {}

          void invoke() const {
            _binder.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1> _binder;
      };

      template<typename T, typename TMF>
      class Method<T, TMF, void> : public virtual sk::rt::action::Item
      {
        public:
          Method(const sk::util::String& label, T& target, const TMF method)
            : Item(label), _target(target), _binder(method) {}

          void invoke() const {
            _binder.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF> _binder;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_METHOD_HXX_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTION_METHODITEM_HXX_
#define _SK_RT_ACTION_METHODITEM_HXX_

#include <sk/rt/action/Item.h>
#include <sk/rt/Callable.hxx>

namespace sk {
  namespace rt {
    namespace action {
      template<typename T, typename TMF, typename P1 = void, typename P2 = void, typename P3 = void>
      class MethodItem : public virtual sk::rt::action::Item
      {
        public:
          MethodItem(const sk::util::String& label, T& target, const TMF method, P1 p1, P2 p2, P3 p3)
            : Item(label), _target(target), _callable(method, p1, p2, p3) {}

          void invoke() const {
            _callable.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1, P2, P3> _callable;
      };

      template<typename T, typename TMF, typename P1, typename P2>
      class MethodItem<T, TMF, P1, P2, void>: public virtual sk::rt::action::Item
      {
        public:
          MethodItem(const sk::util::String& label, T& target, const TMF method, P1 p1, P2 p2)
            : Item(label), _target(target), _callable(method, p1, p2) {}

          void invoke() const {
            _callable.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1, P2> _callable;
      };

      template<typename T, typename TMF, typename P1>
      class MethodItem<T, TMF, P1, void, void>: public virtual sk::rt::action::Item
      {
        public:
          MethodItem(const sk::util::String& label, T& target, const TMF method, P1 p1)
            : Item(label), _target(target), _callable(method, p1) {}

          void invoke() const {
            _callable.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF, P1> _callable;
      };

      template<typename T, typename TMF>
      class MethodItem<T, TMF, void, void, void>: public virtual sk::rt::action::Item
      {
        public:
          MethodItem(const sk::util::String& label, T& target, const TMF method)
            : Item(label), _target(target), _callable(method) {}

          void invoke() const {
            _callable.call(_target);
          }

        public:
          T& _target;
          const sk::rt::Callable<TMF> _callable;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_METHODITEM_HXX_ */

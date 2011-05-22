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

namespace sk {
  namespace rt {
    namespace action {
      template<typename T, typename TMF, typename P = void>
      class Method : public virtual sk::rt::action::Item
      {
        public:
          Method(const sk::util::String& label, T& target, const TMF method, P param)
            : Item(label), _target(target), _method(method), _param(param) {}

          Method(T& target, const TMF method, P param)
            : _target(target), _method(method), _param(param) {}
      
          void invoke() const {
            (_target.*_method)(_param);
          }

        public:
          T& _target;
          const TMF _method;
          P _param;
      };

      template<typename T, typename TMF>
      class Method<T, TMF, void> : public virtual sk::rt::action::Item
      {
        public:
          Method(const sk::util::String& label, T& target, const TMF method)
            : Item(label), _target(target), _method(method) {}

          Method(T& target, const TMF method)
            : _target(target), _method(method) {}
      
          void invoke() const {
            (_target.*_method)();
          }

        public:
          T& _target;
          const TMF _method;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_METHOD_HXX_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTIONS_H_
#define _SK_RT_ACTIONS_H_

#include <sk/util/Object.h>
#include <sk/rt/Runnable.h>
#include <sk/util/ArrayList.hxx>
#include <sk/util/Exception.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    class Actions 
      : public virtual sk::util::Object
    {
      public:
        Actions(bool reverse = false);
        virtual ~Actions();

        template<typename T, typename TMF> 
        void add(const sk::util::String& label, T& target, TMF method);
    
        template<typename T, typename TMF, typename P> 
        void add(const sk::util::String& label, T& target, TMF method, P& param);
    
        template<typename T, typename TMF, typename P> 
        void add(const sk::util::String& label, T& target, TMF method, const P& param);

        int size() const;
        void setReverse(bool state);
        bool isReverse() const;

        void clear();
        void perform();
        int performIgnoreErrors();
        void performThrow(const sk::util::Exception& exception);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
        struct Item : public sk::util::String {
          Item(const sk::util::String& label);
          virtual void invoke() const = 0;
        };

      private:
        Actions(const Actions& other);
        Actions& operator = (const Actions& other);

        void addItem(Item* actionItem);
        void finalize();
        void runActionsCollectExceptions();

        const sk::rt::Scope _scope;
        bool _reverse;
        sk::util::ArrayList<Item> _items;
        sk::util::ArrayList<sk::util::Exception> _exceptions;

        template<typename T, typename TMF> 
        struct MemberFunctionInvocator;

        template<typename T, typename TMF, typename P> 
        struct MemberFunctionWithParamInvocator;
    };
  }
}

template<typename T, typename TMF>
struct sk::rt::Actions::MemberFunctionInvocator : public virtual sk::rt::Actions::Item {
  MemberFunctionInvocator(const sk::util::String& label, T& target, TMF method)
    : Item(label), _target(target), _method(method) {}

  void invoke() const {
    (_target.*_method)();
  }
  T& _target;
  TMF _method;
};

template<typename T, typename TMF>
void
sk::rt::Actions::
add(const sk::util::String& label, T& target, TMF method)
{
  return addItem(new MemberFunctionInvocator<T, TMF>(label, target, method));
}

template<typename T, typename TMF, typename P>
struct sk::rt::Actions::MemberFunctionWithParamInvocator : public virtual sk::rt::Actions::Item {
  MemberFunctionWithParamInvocator(const sk::util::String& label, T& target, TMF method, P& param)
    : Item(label), _target(target), _method(method), _param(param) {}

  void invoke() const {
    (_target.*_method)(_param);
  }
  T& _target;
  TMF _method;
  P& _param;
};

template<typename T, typename TMF, typename P>
void
sk::rt::Actions::
add(const sk::util::String& label, T& target, TMF method, P& param)
{
  return addItem(new MemberFunctionWithParamInvocator<T, TMF, P>(label, target, method, param));
}

template<typename T, typename TMF, typename P>
void
sk::rt::Actions::
add(const sk::util::String& label, T& target, TMF method, const P& param)
{
  return addItem(new MemberFunctionWithParamInvocator<T, TMF, const P>(label, target, method, param));
}

#endif /* _SK_RT_ACTIONS_H_ */

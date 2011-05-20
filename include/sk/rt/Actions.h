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

#include <sk/types.h>
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

        template<typename T> 
        void add(const sk::util::String& label, T& target);

        template<typename P1, typename P2> 
        void add(const sk::util::String& label, P1& p1, P2& p2);
    
        template<typename P1, typename P2> 
        void add(const sk::util::String& label, P1& p1, const P2& p2);
    
        template<typename T, typename TMF, typename P> 
        void add(const sk::util::String& label, T& target, const TMF& method, P& param);
    
        template<typename T, typename TMF, typename P> 
        void add(const sk::util::String& label, T& target, const TMF& method, const P& param);

        void add(const sk::util::String& label, const sk::function<void>::type& function);
        
        int size() const;
        void setReverse(bool state);
        bool isReverse() const;

        void clear();
        void perform();
        void performThrow(const sk::util::Exception& exception);
        int performIgnoreErrors();

        /// Performs actions until it gets to a successful one, in which case 
        /// it stops and returns without errors even if some were collected 
        /// before. It returns a number of exceptions collected, if any.
        /// If all actions end up with exceptions, throw them all enveloped 
        /// in sk::util::CompoundException, reversing the list in case if
        /// reverseErrors is true. 
        int performUntilSuccess(bool reverseErrors = false);
    
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
        bool runActionsCollectExceptions(bool untilSuccess = false);

        const sk::rt::Scope _scope;
        bool _reverse;
        sk::util::ArrayList<Item> _items;
        sk::util::ArrayList<sk::util::Exception> _exceptions;

        template<typename T, typename TMF, typename P> 
        struct MemberFunctionWithParamInvocator;

        template<typename P1, typename P2>
        struct TwoArgumentInvocator;

        template<typename P>
        struct TwoArgumentInvocator<const typename sk::function<void, const P&, void, void>::type, P>;

        template<typename P> 
        struct FunctionWithParamInvocator;
    };
  }
}

template<typename T, typename TMF, typename P>
struct sk::rt::Actions::MemberFunctionWithParamInvocator : public virtual sk::rt::Actions::Item {
  MemberFunctionWithParamInvocator(const sk::util::String& label, T& target, const TMF method, P& param)
    : Item(label), _target(target), _method(method), _param(param) {}

  void invoke() const {
    (_target.*_method)(_param);
  }
  T& _target;
  const TMF _method;
  P& _param;
};

template<typename T, typename TMF, typename P>
void
sk::rt::Actions::
add(const sk::util::String& label, T& target, const TMF& method, P& param)
{
  addItem(new MemberFunctionWithParamInvocator<T, TMF, P>(label, target, method, param));
}

template<typename T, typename TMF, typename P>
void
sk::rt::Actions::
add(const sk::util::String& label, T& target, const TMF& method, const P& param)
{
  addItem(new MemberFunctionWithParamInvocator<T, TMF, const P>(label, target, method, param));
}

template<typename T> 
void 
sk::rt::Actions::
add(const sk::util::String& label, T& target)
{
  add(label, target, &T::operator());
}

template<typename T, typename TMF>
struct sk::rt::Actions::TwoArgumentInvocator : public virtual sk::rt::Actions::Item {
  TwoArgumentInvocator(const sk::util::String& label, T& target, const TMF method)
    : Item(label), _target(target), _method(method) {}

  void invoke() const {
    (_target.*_method)();
  }
  T& _target;
  const TMF _method;
};

template<typename P>
struct sk::rt::Actions::TwoArgumentInvocator<const typename sk::function<void, const P&>::type, P> : public virtual sk::rt::Actions::Item {
  TwoArgumentInvocator(const sk::util::String& label, const typename sk::function<void, const P&>::type& function, const P& param)
    : Item(label), _function(function), _param(param) {}

  void invoke() const {
    (_function)(_param);
  }
  const typename sk::function<void, const P&>::type& _function;
  const P& _param;
};

template<typename P1, typename P2>
void
sk::rt::Actions::
add(const sk::util::String& label, P1& p1, const P2& p2)
{
  addItem(new TwoArgumentInvocator<P1, P2>(label, p1, p2));
}

template<typename P1, typename P2>
void
sk::rt::Actions::
add(const sk::util::String& label, P1& p1, P2& p2)
{
  addItem(new TwoArgumentInvocator<P1, P2>(label, p1, p2));
}

#endif /* _SK_RT_ACTIONS_H_ */

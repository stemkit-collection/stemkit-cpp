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
#include <sk/rt/action/Item.h>

namespace sk {
  namespace rt {
    class Actions 
      : public virtual sk::util::Object
    {
      public:
        Actions(bool reverse = false);
        virtual ~Actions();

        template<typename T, typename TMF> 
        void addMethod(const sk::util::String& label, T& target, const TMF& method);
    
        template<typename T, typename TMF, typename P> 
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P param);
    
        template<typename F> 
        void addFunctor(const sk::util::String& label, const F& functor);
        
        template<typename F, typename P> 
        void addFunctor(const sk::util::String& label, const F& functor, P param);
    
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
    
      private:
        Actions(const Actions& other);
        Actions& operator = (const Actions& other);

        void addItem(sk::rt::action::Item* actionItem);
        void finalize();
        bool runActionsCollectExceptions(bool untilSuccess = false);

        const sk::rt::Scope _scope;
        bool _reverse;
        sk::util::ArrayList<sk::rt::action::Item> _items;
        sk::util::ArrayList<sk::util::Exception> _exceptions;

        template<typename T, typename TMF> 
        struct MethodInvocator;

        template<typename T, typename TMF, typename P> 
        struct MethodWithParamInvocator;

        template<typename F> 
        struct FunctorInvocator;

        template<typename F, typename P> 
        struct FunctorWithParamInvocator;
    };
  }
}

template<typename T, typename TMF>
struct sk::rt::Actions::MethodInvocator : public virtual sk::rt::action::Item {
  MethodInvocator(const sk::util::String& label, T& target, const TMF method)
    : Item(label), _target(target), _method(method) {}

  void invoke() const {
    (_target.*_method)();
  }
  T& _target;
  const TMF _method;
};

template<typename T, typename TMF>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method)
{
  addItem(new MethodInvocator<T, TMF>(label, target, method));
}

template<typename T, typename TMF, typename P>
struct sk::rt::Actions::MethodWithParamInvocator : public virtual sk::rt::action::Item {
  MethodWithParamInvocator(const sk::util::String& label, T& target, const TMF method, P param)
    : Item(label), _target(target), _method(method), _param(param) {}

  void invoke() const {
    (_target.*_method)(_param);
  }
  T& _target;
  const TMF _method;
  P _param;
};

template<typename T, typename TMF, typename P>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P param)
{
  addItem(new MethodWithParamInvocator<T, TMF, P>(label, target, method, param));
}

template<typename F>
struct sk::rt::Actions::FunctorInvocator : public virtual sk::rt::action::Item {
  FunctorInvocator(const sk::util::String& label, const F& functor)
    : Item(label), _functor(functor) {}

  void invoke() const {
    (_functor)();
  }
  const F& _functor;
};


template<typename F> 
void 
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor)
{
  addItem(new FunctorInvocator<F>(label, functor));
}

template<typename F, typename P>
struct sk::rt::Actions::FunctorWithParamInvocator : public virtual sk::rt::action::Item {
  FunctorWithParamInvocator(const sk::util::String& label, const F& functor, P param)
    : Item(label), _functor(functor), _param(param) {}

  void invoke() const {
    (_functor)(_param);
  }
  const F& _functor;
  P _param;
};

template<typename F, typename P> 
void 
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P param)
{
  addItem(new FunctorWithParamInvocator<F, P>(label, functor, param));
}

#endif /* _SK_RT_ACTIONS_H_ */

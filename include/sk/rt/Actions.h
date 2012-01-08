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
#include <sk/rt/action/MethodItem.hxx>
#include <sk/rt/action/FunctorItem.hxx>

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

        template<typename T, typename TMF, typename P1>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1* p1);

        template<typename T, typename TMF, typename P1>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1& p1);

        template<typename T, typename TMF, typename P1>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, const P1& p1);

        template<typename T, typename TMF, typename P1, typename P2>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2* p2);

        template<typename T, typename TMF, typename P1, typename P2>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2& p2);

        template<typename T, typename TMF, typename P1, typename P2>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, const P2& p2);

        template<typename T, typename TMF, typename P1, typename P2, typename P3>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, P3* p3);

        template<typename T, typename TMF, typename P1, typename P2, typename P3>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, P3& p3);

        template<typename T, typename TMF, typename P1, typename P2, typename P3>
        void addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, const P3& p3);

        template<typename F>
        void addFunctor(const sk::util::String& label, const F& functor);

        template<typename F, typename P1>
        void addFunctor(const sk::util::String& label, const F& functor, P1* p1);

        template<typename F, typename P1>
        void addFunctor(const sk::util::String& label, const F& functor, P1& p1);

        template<typename F, typename P1>
        void addFunctor(const sk::util::String& label, const F& functor, const P1& p1);

        template<typename F, typename P1, typename P2>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2* p2);

        template<typename F, typename P1, typename P2>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2& p2);

        template<typename F, typename P1, typename P2>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, const P2& p2);

        template<typename F, typename P1, typename P2, typename P3>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, P3* p3);

        template<typename F, typename P1, typename P2, typename P3>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, P3& p3);

        template<typename F, typename P1, typename P2, typename P3>
        void addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, const P3& p3);

        int size() const;
        sk::rt::Actions& setReverse(bool state);
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
        const bool _notice;
        bool _reverse;
        sk::util::ArrayList<sk::rt::action::Item> _items;
        sk::util::ArrayList<sk::util::Exception> _exceptions;
    };
  }
}

template<typename T, typename TMF>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method)
{
  addItem(new sk::rt::action::MethodItem<T, TMF>(label, target, method));
}

template<typename T, typename TMF, typename P1>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1* p1)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1*>(label, target, method, p1));
}

template<typename T, typename TMF, typename P1>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1& p1)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1&>(label, target, method, p1));
}

template<typename T, typename TMF, typename P1>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, const P1& p1)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1>(label, target, method, p1));
}

template<typename T, typename TMF, typename P1, typename P2>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2* p2)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2*>(label, target, method, p1, p2));
}

template<typename T, typename TMF, typename P1, typename P2>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2& p2)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2&>(label, target, method, p1, p2));
}

template<typename T, typename TMF, typename P1, typename P2>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, const P2& p2)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2>(label, target, method, p1, p2));
}

template<typename T, typename TMF, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, P3* p3)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2, P3*>(label, target, method, p1, p2, p3));
}

template<typename T, typename TMF, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, P3& p3)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2, P3&>(label, target, method, p1, p2, p3));
}

template<typename T, typename TMF, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addMethod(const sk::util::String& label, T& target, const TMF& method, P1 p1, P2 p2, const P3& p3)
{
  addItem(new sk::rt::action::MethodItem<T, TMF, P1, P2, P3>(label, target, method, p1, p2, p3));
}

template<typename F>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor)
{
  addItem(new sk::rt::action::FunctorItem<F>(label, functor));
}

template<typename F, typename P1>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1* p1)
{
  addItem(new sk::rt::action::FunctorItem<F, P1*>(label, functor, p1));
}

template<typename F, typename P1>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1& p1)
{
  addItem(new sk::rt::action::FunctorItem<F, P1&>(label, functor, p1));
}

template<typename F, typename P1>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, const P1& p1)
{
  addItem(new sk::rt::action::FunctorItem<F, P1>(label, functor, p1));
}

template<typename F, typename P1, typename P2>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2* p2)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2*>(label, functor, p1, p2));
}

template<typename F, typename P1, typename P2>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2& p2)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2&>(label, functor, p1, p2));
}

template<typename F, typename P1, typename P2>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, const P2& p2)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2>(label, functor, p1, p2));
}

template<typename F, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, P3* p3)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2, P3*>(label, functor, p1, p2, p3));
}

template<typename F, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, P3& p3)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2, P3&>(label, functor, p1, p2, p3));
}

template<typename F, typename P1, typename P2, typename P3>
void
sk::rt::Actions::
addFunctor(const sk::util::String& label, const F& functor, P1 p1, P2 p2, const P3& p3)
{
  addItem(new sk::rt::action::FunctorItem<F, P1, P2, P3>(label, functor, p1, p2, p3));
}

#endif /* _SK_RT_ACTIONS_H_ */

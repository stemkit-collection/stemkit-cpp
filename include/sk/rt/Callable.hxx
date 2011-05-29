/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_CALLABLE_HXX_
#define _SK_RT_CALLABLE_HXX_

namespace sk {
  namespace rt {
    template<typename C, typename P1 = void, typename P2 = void, typename P3 = void>
    class Callable 
    {
      public:
        Callable(const C callable, P1 p1, P2 p2, P3 p3)
          : _callable(callable), _p1(p1), _p2(p2), _p3(p3) {}
    
        template<typename T>
        void callTarget(T& target) const {
          (target.*_callable)(_p1, _p2, _p3);
        }
        template<typename T, typename E>
        void callTarget(T& target, E& extra) const {
          (target.*_callable)(extra, _p1, _p2, _p3);
        }
        template<typename E>
        void call(E& extra) const {
          (_callable)(extra, _p1, _p2, _p3);
        }
        void call() const {
          (_callable)(_p1, _p2, _p3);
        }

      private:
        const C _callable;
        P1 _p1;
        P2 _p2;
        P3 _p3;
    };

    template<typename C, typename P1, typename P2>
    class Callable<C, P1, P2, void>
    {
      public:
        Callable(const C callable, P1 p1, P2 p2)
          : _callable(callable), _p1(p1), _p2(p2) {}
    
        template<typename T>
        void callTarget(T& target) const {
          (target.*_callable)(_p1, _p2);
        }
        template<typename T, typename E>
        void callTarget(T& target, E& extra) const {
          (target.*_callable)(extra, _p1, _p2);
        }
        template<typename E>
        void call(E& extra) const {
          (_callable)(extra, _p1, _p2);
        }
        void call() const {
          (_callable)(_p1, _p2);
        }

      private:
        const C _callable;
        P1 _p1;
        P2 _p2;
    };

    template<typename C, typename P1>
    class Callable<C, P1, void, void>
    {
      public:
        Callable(const C callable, P1 p1)
          : _callable(callable), _p1(p1) {}
    
        template<typename T>
        void callTarget(T& target) const {
          (target.*_callable)(_p1);
        }
        template<typename T, typename E>
        void callTarget(T& target, E& extra) const {
          (target.*_callable)(extra, _p1);
        }
        template<typename E>
        void call(E& extra) const {
          (_callable)(extra, _p1);
        }
        void call() const {
          (_callable)(_p1);
        }

      private:
        const C _callable;
        P1 _p1;
    };

    template<typename C>
    class Callable<C, void, void, void>
    {
      public:
        Callable(const C callable)
          : _callable(callable) {}
    
        template<typename T>
        void callTarget(T& target) const {
          (target.*_callable)();
        }
        template<typename T, typename E>
        void callTarget(T& target, E& extra) const {
          (target.*_callable)(extra);
        }
        template<typename E>
        void call(E& extra) const {
          (_callable)(extra);
        }
        void call() const {
          (_callable)();
        }

      private:
        const C _callable;
    };
  }
}

#endif /* _SK_RT_CALLABLE_HXX_ */

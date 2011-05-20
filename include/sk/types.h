/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_TYPES_H_
#define _SK_TYPES_H_

namespace sk {
  template<typename R, typename P1 = void, typename P2 = void, typename P3 = void>
  struct function {
    typedef R (type)(P1 p1, P2 p2, P3 p3);
  };

  template<typename R, typename P1, typename P2> struct function<R, P1, P2, void> {
    typedef R (type)(P1 p1, P2 p2);
  };

  template<typename R, typename P> struct function<R, P, void, void> {
    typedef R (type)(P p);
  };

  template<typename R> struct function<R, void, void, void> {
    typedef R (type)();
  };
}


#endif /* _SK_TYPES_H_ */

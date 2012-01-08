/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SELECTOR_
#define _SK_UTIL_SELECTOR_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    template<typename T>
    class Selector
      : public virtual sk::util::Object
    {
      public:
        virtual bool assess(const T& object) const = 0;
    };
  }
}

#endif /* _SK_UTIL_SELECTOR_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_BREAK_H_
#define _SK_UTIL_BREAK_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Break
      : public virtual sk::util::Object
    {
      public:
        Break();
        virtual ~Break();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_BREAK_H_ */

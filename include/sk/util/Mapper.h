/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_MAPPER_H_
#define _SK_UTIL_MAPPER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    template<typename F, typename T = F>
    class Mapper
      : public virtual sk::util::Object
    {
      public:
        virtual T map(F& object) const = 0;
    };
  }
}

#endif /* _SK_UTIL_MAPPER_H_ */

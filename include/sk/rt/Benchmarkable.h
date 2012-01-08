/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_BENCHMARKABLE_H_
#define _SK_RT_BENCHMARKABLE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    class Benchmarkable
      : public virtual sk::util::Object
    {
      public:
        virtual void setup() = 0;
        virtual void run() = 0;
        virtual void reset() = 0;
    };
  }
}

#endif /* _SK_RT_BENCHMARKABLE_H_ */

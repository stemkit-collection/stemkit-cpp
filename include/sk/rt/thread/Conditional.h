/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_CONDITIONAL_H_
#define _SK_RT_THREAD_CONDITIONAL_H_

#include <sk/util/Object.h>
#include <sk/rt/thread/Condition.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Conditional
        : public virtual sk::util::Object
      {
        public:
          virtual void process(sk::rt::thread::Condition& condition) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_CONDITIONAL_H_ */

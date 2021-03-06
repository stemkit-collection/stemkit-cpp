/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_CONDITION_H_
#define _SK_RT_THREAD_CONDITION_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Condition
        : public virtual sk::util::Object
      {
        public:
          virtual sk::rt::thread::Condition& on(int channel) = 0;
          virtual void wait(uint64_t milliseconds = 0) = 0;
          virtual void announce() = 0;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_CONDITION_H_ */

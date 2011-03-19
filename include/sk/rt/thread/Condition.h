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
          virtual void ensure(bool expression, uint64_t timeout = 0) = 0;
          virtual void ensure(int channel, bool expression, uint64_t timeout = 0) = 0;
          virtual void announce(bool expression) = 0;
          virtual void announce(int channel, bool expression) = 0;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_CONDITION_H_ */

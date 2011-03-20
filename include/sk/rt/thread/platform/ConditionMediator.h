/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PLATFORM_CONDITIONMEDIATOR_H_
#define _SK_RT_THREAD_PLATFORM_CONDITIONMEDIATOR_H_

#include <sk/rt/thread/Conditional.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace platform {
        class ConditionMediator 
          : public virtual sk::util::Object
        {
          public:
            virtual void invoke(const sk::rt::thread::Conditional& block) = 0; 
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PLATFORM_CONDITIONMEDIATOR_H_ */

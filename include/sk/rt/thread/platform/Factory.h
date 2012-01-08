/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_PLATFORM_FACTORY_H_
#define _SK_RT_THREAD_PLATFORM_FACTORY_H_

#include <sk/util/Object.h>
#include <sk/rt/thread/platform/Implementation.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace platform {
        class Factory
          : public virtual sk::util::Object
        {
          public:
            platform::Implementation* makeImplementation() const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PLATFORM_FACTORY_H_ */

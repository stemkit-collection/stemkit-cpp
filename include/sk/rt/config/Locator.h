/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_LOCATOR_
#define _SK_RT_CONFIG_LOCATOR_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace config {
      class StreamProcessor;

      class Locator
        : public virtual sk::util::Object
      {
        public:
          virtual void invoke(const StreamProcessor& processor) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_LOCATOR_ */

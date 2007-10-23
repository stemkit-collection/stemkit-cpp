/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_CONFIG_
#define _SK_RT_SCOPE_CONFIG_

#include <sk/rt/logger/Config.h>
#include <sk/util/String.h>

namespace sk {
  namespace rt {
    namespace scope {
      class Config
        : public virtual sk::rt::logger::Config
      {
        public:
          virtual const sk::util::String getProperty(const sk::util::String& name) const = 0;
          virtual bool hasProperty(const sk::util::String& name) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONFIG_ */

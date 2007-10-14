/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_SCOPEPROVIDER_
#define _SK_RT_LOGGER_SCOPEPROVIDER_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;

      class ScopeProvider
        : public virtual sk::util::Object 
      {
        public:
          virtual const sk::rt::logger::Config& config() const = 0;
          virtual const sk::util::String getScopeName() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_SCOPEPROVIDER_ */

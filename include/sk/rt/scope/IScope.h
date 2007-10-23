/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_ILOGGER_
#define _SK_RT_SCOPE_ILOGGER_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;
    }
    namespace scope {
      class IScope
        : public virtual sk::util::Object 
      {
        public:
          virtual const logger::Config& getConfig() const = 0;
          virtual const sk::util::Object& getObject() const = 0;
          virtual void agregateScopeName(std::ostream& stream) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_ILOGGER_ */

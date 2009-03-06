/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_ISCOPE_
#define _SK_RT_LOGGER_ISCOPE_

#include <sk/util/Object.h>
#include <sk/rt/scope/Arbitrator.h>

namespace sk {
  namespace rt {
    namespace logger {
      class IConfig;

      class IScope
        : public virtual sk::util::Object 
      {
        public:
          virtual const logger::IConfig& getConfig() const = 0;
          virtual const sk::util::Object& getObject() const = 0;
          virtual void aggregateScopeName(std::ostream& stream) const = 0;
          virtual uint64_t currentThreadId() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ISCOPE_ */

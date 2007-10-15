/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_ILOGGER_
#define _SK_RT_LOGGER_ILOGGER_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;

      class ILogger
        : public virtual sk::util::Object 
      {
        public:
          virtual const sk::rt::logger::Config& getConfig() const = 0;
          virtual const sk::util::Object& getObject() const = 0;
          virtual void serializeScope(std::ostream& stream) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ILOGGER_ */

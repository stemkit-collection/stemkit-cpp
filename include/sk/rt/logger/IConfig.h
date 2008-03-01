/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_ICONFIG_
#define _SK_RT_LOGGER_ICONFIG_

#include <sk/util/Object.h>
#include <sk/rt/logger/Destination.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;

      class IConfig
        : public virtual sk::util::Object 
      {
        public:
          virtual bool checkLogLevel(const Level& level) const = 0;
          virtual logger::Destination& getLogDestination() const = 0;
          virtual const char* getTimeFormat() const = 0;
          virtual bool isLogPid() const = 0;
          virtual bool isLogTime() const = 0;
          virtual bool isLogObject() const = 0;

          virtual void setLogDestination(const logger::Destination& destination) = 0;
          virtual void setLogLevel(const logger::Level& level) = 0;
          virtual void setTimeFormat(const sk::util::String& format) = 0;
          virtual void setLogPid(bool state) = 0;
          virtual void setLogTime(bool state) = 0;
          virtual void setLogObject(bool state) = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ICONFIG_ */

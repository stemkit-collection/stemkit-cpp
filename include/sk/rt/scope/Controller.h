/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_CONTROLLER_
#define _SK_RT_SCOPE_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/scope/Config.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;
    }
    namespace scope {
      class Controller
        : public virtual scope::Config
      {
        public:
          Controller();
          virtual ~Controller();

          void setLogStream(std::ostream& stream);
          void setLogLevel(const logger::Level& level);

          void setLogPid(bool state);
          void setLogTime(bool state);
          void setLogObject(bool state);

          scope::Config& findConfig(const sk::util::String& name);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::rt::logger::Config implementation.
          std::ostream& getLogStream() const;
          bool checkLogLevel(const logger::Level& level) const;
          bool isLogPid() const;
          bool isLogTime() const;
          bool isLogObject() const;
          
          // sk::rt::scope::Config implementation.
          const sk::util::String getProperty(const sk::util::String& name) const;
          bool hasProperty(const sk::util::String& name) const;
          
        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          sk::util::Holder<std::ostream> _streamHolder;
          sk::util::Holder<const logger::Level> _levelHolder;
          bool _showPid;
          bool _showTime;
          bool _showObject;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONTROLLER_ */

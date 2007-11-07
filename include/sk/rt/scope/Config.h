/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_CONFIG_
#define _SK_RT_SCOPE_CONFIG_

#include <sk/util/Holder.hxx>
#include <sk/rt/scope/IConfig.h>
#include <map>

namespace sk {
  namespace rt {
    namespace scope {
      class Config
        : public virtual scope::IConfig
      {
        public:
          Config();
          Config(const Config& other);
          virtual ~Config();
          
          void setLogStream(std::ostream& stream);
          void setLogLevel(const logger::Level& level);

          void setLogPid(bool state);
          void setLogTime(bool state);
          void setLogObject(bool state);
          void setProperty(const sk::util::String& name, const sk::util::String& value);

          // sk::rt::logger::IConfig implementation.
          std::ostream& getLogStream() const;
          bool checkLogLevel(const logger::Level& level) const;
          bool isLogPid() const;
          bool isLogTime() const;
          bool isLogObject() const;
          
          // sk::rt::scope::Config implementation.
          const sk::util::String getProperty(const sk::util::String& name) const;
          const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const;
          const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const;
          bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const;
          int getProperty(const sk::util::String& name, int fallback) const;
          bool hasProperty(const sk::util::String& name) const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Config& operator = (const Config& other);

          sk::util::Holder<std::ostream> _streamHolder;
          sk::util::Holder<const logger::Level> _levelHolder;

          bool _logPid;
          bool _logTime;
          bool _logObject;
          typedef std::map<sk::util::String, sk::util::String> registry;
          registry _properties;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONFIG_ */

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
          virtual ~Config();
          
          void setLogDestination(const logger::Destination& destination);
          void setLogLevel(const logger::Level& level);
          void setTimeFormat(const sk::util::String& format);

          void setLogPid(bool state);
          void setLogTime(bool state);
          void setLogObject(bool state);
          void setLogThread(bool state);
          void setProperty(const sk::util::String& name, const sk::util::String& value);

          // sk::rt::logger::IConfig implementation.
          logger::Destination& getLogDestination() const;
          bool checkLogLevel(const logger::Level& level) const;
          const char* getTimeFormat() const;
          bool isLogPid() const;
          bool isLogTime() const;
          bool isLogObject() const;
          bool isLogThread() const;
          
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

          sk::util::Holder<logger::Destination>::Sharing _destinationHolder;
          sk::util::Holder<const logger::Level>::Aliasing _levelHolder;

          bool _logPid;
          bool _logTime;
          bool _logObject;
          bool _logThread;
          sk::util::String _timeFormat;
          typedef std::map<sk::util::String, sk::util::String> registry;
          registry _properties;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONFIG_ */

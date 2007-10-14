/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_CONTROLLER_
#define _SK_RT_LOGGER_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/logger/Config.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;

      class Controller
        : public virtual sk::rt::logger::Config
      {
        public:
          Controller();
          virtual ~Controller();

          void setStream(std::ostream& stream);
          void setLevel(const Level& level);

          void setShowPid(bool state);
          void setShowTime(bool state);
          void setShowObject(bool state);

          const Level& getLevel() const;
          Config& findConfig(const sk::util::String& name);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::rt::logger::Config implementation.
          std::ostream& getStream() const;
          bool checkLevel(const sk::rt::logger::Level& level) const;
          bool isShowPid() const;
          bool isShowTime() const;
          bool isShowObject() const;
          
        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          sk::util::Holder<std::ostream> _streamHolder;
          sk::util::Holder<const Level> _levelHolder;
          bool _showPid;
          bool _showTime;
          bool _showObject;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CONTROLLER_ */

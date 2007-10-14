/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_DISABLINGCONFIG_
#define _SK_RT_LOGGER_DISABLINGCONFIG_

#include <sk/rt/logger/Config.h>

namespace sk {
  namespace rt {
    namespace logger {
      class DisablingConfig
        : public virtual sk::rt::logger::Config
      {
        public:
          DisablingConfig();
          virtual ~DisablingConfig();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::rt::logger::Config implementation.
          bool checkLevel(const Level& level) const;
          std::ostream& stream() const;
          
        private:
          DisablingConfig(const DisablingConfig& other);
          DisablingConfig& operator = (const DisablingConfig& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_DISABLINGCONFIG_ */

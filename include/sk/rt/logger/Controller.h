/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_CONTROLLER_
#define _SK_RT_LOGGER_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/rt/logger/Config.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;

      class Controller
        : public virtual sk::util::Object 
      {
        public:
          Controller();
          virtual ~Controller();

          Config& findConfig(const sk::util::String& name);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          Config _defaultConfig;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CONTROLLER_ */

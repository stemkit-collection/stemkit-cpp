/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_CONFIG_
#define _SK_RT_LOGGER_CONFIG_

#include <sk/util/Object.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;

      class Config
        : public virtual sk::util::Object 
      {
        public:
          virtual bool checkLevel(const Level& level) const = 0;
          virtual std::ostream& getStream() const = 0;
          virtual bool isShowPid() const = 0;
          virtual bool isShowTime() const = 0;
          virtual bool isShowObject() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CONFIG_ */

/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_CONFIG_
#define _SK_RT_LOGGER_CONFIG_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config
        : public virtual sk::util::Object 
      {
        public:
          Config();
          virtual ~Config();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Config(const Config& other);
          Config& operator = (const Config& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CONFIG_ */

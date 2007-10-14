/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_ICONTROLLER_
#define _SK_RT_LOGGER_ICONTROLLER_

#include <sk/util/Object.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class IController
        : public virtual sk::util::Object 
      {
        public:
          virtual std::ostream& getStream() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ICONTROLLER_ */

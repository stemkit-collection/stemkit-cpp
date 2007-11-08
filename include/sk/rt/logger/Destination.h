/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_DESTINATION_
#define _SK_RT_LOGGER_DESTINATION_

#include <sk/util/Object.h>
#include <sstream>

namespace sk {
  namespace rt {
    namespace logger {
      class Destination
        : public virtual sk::util::Object 
      {
        public:
          virtual void dispatch(std::stringstream& stream) = 0;
          virtual Destination* clone() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_DESTINATION_ */

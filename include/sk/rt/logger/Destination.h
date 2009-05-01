/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_DESTINATION_
#define _SK_RT_LOGGER_DESTINATION_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace rt {
    namespace logger {
      class Destination
        : public virtual sk::util::Object 
      {
        public:
          virtual void dispatch(const char* buffer, int size) = 0;
          virtual const std::vector<int> makeReady() = 0;
          virtual sk::util::Object* clone() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_DESTINATION_ */

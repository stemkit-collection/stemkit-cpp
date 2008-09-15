/*  vim: set sw=2:
 *
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_CYCLER_H_
#define _SK_RT_LOGGER_CYCLER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Cycler
        : public virtual sk::util::Object 
      {
        public:
          virtual Cycler* clone() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CYCLER_H_ */

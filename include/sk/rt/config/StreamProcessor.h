/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_STREAMPROCESSOR_
#define _SK_RT_CONFIG_STREAMPROCESSOR_

#include <sk/util/Object.h>
#include <sk/util/Pathname.h>
#include <istream>

namespace sk {
  namespace rt {
    namespace config {
      class StreamProcessor
        : public virtual sk::util::Object
      {
        public:
          virtual void process(std::istream& stream, const sk::util::Pathname& location) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_STREAMPROCESSOR_ */

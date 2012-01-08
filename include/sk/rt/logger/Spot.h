/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_SPOT_
#define _SK_RT_LOGGER_SPOT_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Spot
        : public virtual sk::util::Object
      {
        public:
          Spot(const Spot& other);
          virtual ~Spot();

          static Spot function(const sk::util::String& name, int line);
          static Spot file(const sk::util::String& name, int line);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // Constants.
          static const Spot UNKNOWN;
          static const Spot NOTSET;

        private:
          Spot();
          Spot& operator = (const Spot& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_SPOT_ */

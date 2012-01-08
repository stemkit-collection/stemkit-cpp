/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_STABLECYCLER_H_
#define _SK_RT_LOGGER_STABLECYCLER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class StableCycler
        : public virtual sk::util::Object
      {
        public:
          StableCycler();
          virtual ~StableCycler();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          StableCycler(const StableCycler& other);
          StableCycler& operator = (const StableCycler& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_STABLECYCLER_H_ */

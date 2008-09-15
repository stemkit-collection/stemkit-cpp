/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_STABLEHEADCYCLER_H_
#define _SK_RT_LOGGER_STABLEHEADCYCLER_H_

#include <sk/util/Object.h>
#include "Cycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class StableHeadCycler
        : public virtual Cycler
      {
        public:
          StableHeadCycler();
          virtual ~StableHeadCycler();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // Cycler re-implementation.
          StableHeadCycler* clone() const;
          
        private:
          StableHeadCycler& operator = (const StableHeadCycler& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_STABLEHEADCYCLER_H_ */

/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_ABSTRACTCYCLER_H_
#define _SK_RT_LOGGER_ABSTRACTCYCLER_H_

#include "Cycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class AbstractCycler
        : public virtual Cycler
      {
        public:
          AbstractCycler();
          virtual ~AbstractCycler();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          AbstractCycler& operator = (const AbstractCycler& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ABSTRACTCYCLER_H_ */

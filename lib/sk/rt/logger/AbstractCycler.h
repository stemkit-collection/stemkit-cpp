/*  vi: set sw=2:
 *
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_ABSTRACTCYCLER_H_
#define _SK_RT_LOGGER_ABSTRACTCYCLER_H_

#include <sk/util/Pathname.h>
#include <sk/util/String.h>
#include "Cycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class AbstractCycler
        : public virtual Cycler
      {
        public:
          AbstractCycler(const sk::util::Pathname& masterPathname);
          virtual ~AbstractCycler();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        protected:
          const sk::util::Pathname& getMasterPathname() const;
          
        private:
          AbstractCycler& operator = (const AbstractCycler& other);

          sk::util::Pathname _masterPathname;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ABSTRACTCYCLER_H_ */

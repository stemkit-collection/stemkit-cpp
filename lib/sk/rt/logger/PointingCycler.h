/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_POINTINGCYCLER_H_
#define _SK_RT_LOGGER_POINTINGCYCLER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class PointingCycler
        : public virtual sk::util::Object 
      {
        public:
          PointingCycler();
          virtual ~PointingCycler();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          PointingCycler(const PointingCycler& other);
          PointingCycler& operator = (const PointingCycler& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_POINTINGCYCLER_H_ */

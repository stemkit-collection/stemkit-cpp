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

#include <sk/util/Pathname.h>
#include "AbstractCycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class PointingCycler
        : public AbstractCycler
      {
        public:
          PointingCycler(const sk::util::Pathname& pathname);
          virtual ~PointingCycler();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // Cycler implementation.
          sk::util::Object* clone() const;
          const sk::util::String getPath() const;

        protected:
          // AbstractCycler implementation.
          void ensureChunks();
          bool scanFile();
          void initFile();
          void cycleFile();
          
        private:
          PointingCycler& operator = (const PointingCycler& other);

          int _chunk;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_POINTINGCYCLER_H_ */

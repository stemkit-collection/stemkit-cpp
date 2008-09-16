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
#include "AbstractCycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class StableHeadCycler
        : public AbstractCycler
      {
        public:
          StableHeadCycler(const sk::util::Pathname& pathname);
          virtual ~StableHeadCycler();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // Cycler re-implementation.
          StableHeadCycler* clone() const;
          void initChunk();
          const sk::util::String getPath() const;
          
        protected:
          // AbstractCycler implementation.
          void backupFile();
          void initFile();
          
        private:
          StableHeadCycler& operator = (const StableHeadCycler& other);

          const sk::util::Pathname& getPathname() const;
          bool scanFile();

          int _nextBackup;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_STABLEHEADCYCLER_H_ */

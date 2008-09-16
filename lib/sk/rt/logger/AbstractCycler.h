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
          
          // Cycler re-implementation.
          int getSize() const;
          void setSize(const sk::util::String& specification);
          void setSize(int size);
          int getChunks() const;
          void setChunks(const sk::util::String& specification);
          void setChunks(int chunks);
          off_t offset() const;
          bool advance(off_t size);
          void init();

        protected:
          const sk::util::Pathname& getMasterPathname() const;
          bool readMarker(const sk::util::String& path, int& chunk) const;
          void writeMarker(const sk::util::String& path, int chunk);
          const sk::util::String makeChunkPath(int number) const;

          virtual bool scanFile() = 0;
          virtual void initFile() = 0;
          virtual void cycleFile() = 0;
          
        private:
          AbstractCycler& operator = (const AbstractCycler& other);

          sk::util::Pathname _masterPathname;
          int _size;
          int _chunks;
          off_t _bytesWritten;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_ABSTRACTCYCLER_H_ */

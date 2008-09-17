/*  vim: set sw=2:
 *
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_CYCLER_H_
#define _SK_RT_LOGGER_CYCLER_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Cycler
        : public virtual sk::util::Object 
      {
        public:
          virtual Cycler* clone() const = 0;
          virtual void ensureChunks() = 0;

          virtual off_t offset() const = 0;
          virtual void init() = 0;
          virtual bool advance(off_t size) = 0;
          virtual const sk::util::String getPath() const = 0;

          virtual int getSize() const = 0;
          virtual void setSize(const sk::util::String& specification) = 0;
          virtual void setSize(int size) = 0;

          virtual int getChunks() const = 0;
          virtual void setChunks(const sk::util::String& specification) = 0;
          virtual void setChunks(int chunks) = 0;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CYCLER_H_ */

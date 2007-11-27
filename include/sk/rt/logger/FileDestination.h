/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_FILEDESTINATION_
#define _SK_RT_LOGGER_FILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Pathname.h>

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination
        : public virtual Destination
      {
        public:
          FileDestination(const sk::util::Pathname& pathname);
          virtual ~FileDestination();

          void setSize(const sk::util::String& specification);
          void setChunks(const sk::util::String& specification);

          // sk::rt::logger::Destination implementation.
          void dispatch(std::stringstream& stream);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          FileDestination* clone() const;
          
        private:
          FileDestination& operator = (const FileDestination& other);
          sk::util::Pathname _pathname;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

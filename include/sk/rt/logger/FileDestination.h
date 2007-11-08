/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_FILEDESTINATION_
#define _SK_RT_LOGGER_FILEDESTINATION_

#include <sk/rt/logger/Destination.h>

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination
        : public virtual Destination
      {
        public:
          FileDestination();
          virtual ~FileDestination();

          // sk::rt::logger::Destination implementation.
          void dispatch(std::stringstream& stream);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          FileDestination(const FileDestination& other);
          FileDestination& operator = (const FileDestination& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

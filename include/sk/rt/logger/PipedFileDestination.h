/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_PIPEDFILEDESTINATION_
#define _SK_RT_LOGGER_PIPEDFILEDESTINATION_

#include <sk/rt/logger/FileDestination.h>
#include <sk/util/Pathname.h>

namespace sk {
  namespace rt {
    namespace logger {
      class PipedFileDestination
        : public FileDestination
      {
        public:
          PipedFileDestination(const sk::util::Pathname& pathname);
          virtual ~PipedFileDestination();
          
          // sk::rt::logger::Destination implementation.
          void dispatch(std::stringstream& stream);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          PipedFileDestination* clone() const;
          
        private:
          PipedFileDestination& operator = (const PipedFileDestination& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_PIPEDFILEDESTINATION_ */

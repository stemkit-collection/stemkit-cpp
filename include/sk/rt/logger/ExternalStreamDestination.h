/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_EXTERNALSTREAMDESTINATION_
#define _SK_RT_LOGGER_EXTERNALSTREAMDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class ExternalStreamDestination
        : public virtual Destination
      {
        public:
          ExternalStreamDestination(std::ostream& destination);
          virtual ~ExternalStreamDestination();

          // sk::rt::logger::Destinaiton implementation.
          void dispatch(std::stringstream& stream);
          ExternalStreamDestination* clone() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          ExternalStreamDestination& operator = (const ExternalStreamDestination& other);

          std::ostream& _destination;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_EXTERNALSTREAMDESTINATION_ */

/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_STREAMDESTINATION_
#define _SK_RT_LOGGER_STREAMDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class StreamDestination
        : public virtual Destination
      {
        public:
          StreamDestination(std::ostream& destination);
          virtual ~StreamDestination();

          // sk::rt::logger::Destinaiton implementation.
          void dispatch(const char* buffer, int size);
          const std::vector<int> makeReady();
          sk::util::Object* clone() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          StreamDestination& operator = (const StreamDestination& other);

          std::ostream& _destination;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_STREAMDESTINATION_ */

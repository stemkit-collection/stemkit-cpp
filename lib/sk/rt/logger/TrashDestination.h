/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_TRASHDESTINATION_H_
#define _SK_RT_LOGGER_TRASHDESTINATION_H_

#include <sk/rt/logger/Destination.h>

namespace sk {
  namespace rt {
    namespace logger {
      class TrashDestination
        : public virtual Destination
      {
        public:
          TrashDestination();
          virtual ~TrashDestination();

          // sk::rt::logger::Destinaiton implementation.
          void dispatch(const char* buffer, int size);
          void makeReady();
          TrashDestination* clone() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          TrashDestination& operator = (const TrashDestination& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_TRASHDESTINATION_H_ */

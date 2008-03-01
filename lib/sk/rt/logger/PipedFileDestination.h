/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_PIPEDFILEDESTINATION_
#define _SK_RT_LOGGER_PIPEDFILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace logger {
      class PipedFileDestination
        : public virtual logger::Destination
      {
        public:
          PipedFileDestination(const logger::Destination& destination);
          PipedFileDestination(const PipedFileDestination& other);
          virtual ~PipedFileDestination();
          
          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          void makeReady();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          PipedFileDestination* clone() const;
          
        private:
          PipedFileDestination& operator = (const PipedFileDestination& other);

          void cleanup();
          void makePipe();
          void waitData(int descriptor);
          int cloneDescriptor() const;

          int _descriptor;
          sk::util::Holder<logger::Destination>::Cloning _destinationHolder;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_PIPEDFILEDESTINATION_ */

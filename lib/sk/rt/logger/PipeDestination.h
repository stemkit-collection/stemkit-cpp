/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_PIPEDESTINATION_
#define _SK_RT_LOGGER_PIPEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace logger {
      class PipeDestination
        : public virtual logger::Destination
      {
        public:
          PipeDestination(const logger::Destination& destination);
          PipeDestination(const PipeDestination& other);
          virtual ~PipeDestination();
          
          void close();

          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          const std::vector<int> makeReady();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          PipeDestination* clone() const;
          
        private:
          PipeDestination& operator = (const PipeDestination& other);

          void cleanup();
          void makePipe();
          void waitData(int descriptor);
          int cloneDescriptor() const;
          void output(const sk::util::String& message);

          int _descriptor;
          bool _piped;
          sk::util::Holder<logger::Destination>::Cloning _destinationHolder;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_PIPEDESTINATION_ */

/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_FILEDESTINATION_
#define _SK_RT_LOGGER_FILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Holder.hxx>
#include <sk/util/Pathname.h>
#include "DataWriter.h"
#include "Cycler.h"

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination
        : public virtual logger::Destination,
          public virtual DataWriter
      {
        public:
          FileDestination(const sk::util::Pathname& pathname);
          FileDestination(const Cycler& cycler);
          FileDestination(const FileDestination& other);
          virtual ~FileDestination();

          const Cycler& getCycler() const;
          Cycler& getCycler();
          
          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          const std::vector<int> makeReady();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          FileDestination* clone() const;

          // DataWriter implementation.
          void writeData(const char* data);
          void writeData(const char* data, int size);
          
        private:
          FileDestination& operator = (const FileDestination& other);

          void openFile();
          void closeFile();

          int cloneDescriptor() const;

          int _descriptor;
          sk::util::Holder<Cycler> _cyclerHolder;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

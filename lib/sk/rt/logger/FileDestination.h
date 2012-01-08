/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_FILEDESTINATION_
#define _SK_RT_LOGGER_FILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/rt/scope/Arbitrator.h>
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
          FileDestination(const sk::util::Pathname& pathname, scope::Arbitrator& arbitrator);
          FileDestination(const Cycler& cycler, scope::Arbitrator& arbitrator);
          FileDestination(const FileDestination& other);
          virtual ~FileDestination();

          void close();
          const Cycler& getCycler() const;
          Cycler& getCycler();

          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          const std::vector<int> makeReady();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          sk::util::Object* clone() const;

          // DataWriter implementation.
          void writeData(const char* data);
          void writeData(const char* data, int size);

        private:
          FileDestination& operator = (const FileDestination& other);

          void ensureFile();
          void closeFile();

          int cloneDescriptor() const;

          int _descriptor;
          sk::util::Holder<Cycler> _cyclerHolder;
          scope::Arbitrator& _arbitrator;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

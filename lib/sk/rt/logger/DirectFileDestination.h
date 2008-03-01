/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_DIRECTFILEDESTINATION_
#define _SK_RT_LOGGER_DIRECTFILEDESTINATION_

#include <logger/FileDestination.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>
#include <fstream>

namespace sk {
  namespace rt {
    namespace logger {
      class DirectFileDestination
        : public FileDestination
      {
        public:
          DirectFileDestination(const sk::util::Pathname& pathname);
          virtual ~DirectFileDestination();

          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          
          // sk::util::Logger::FileDestination implementation.
          void makeReady();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          DirectFileDestination* clone() const;
          
        private:
          DirectFileDestination& operator = (const DirectFileDestination& other);

          void openFile();
          void closeFile();
          void backupFile();
          void initFile();
          bool scanFile();

          int _nextBackup;
          off_t _bytesWritten;
          sk::util::Holder<std::fstream>::Sharing _fileHolder;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_DIRECTFILEDESTINATION_ */

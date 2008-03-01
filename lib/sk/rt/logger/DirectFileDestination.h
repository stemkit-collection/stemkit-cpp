/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_DIRECTFILEDESTINATION_
#define _SK_RT_LOGGER_DIRECTFILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>
#include <fstream>

namespace sk {
  namespace rt {
    namespace logger {
      class DirectFileDestination
        : public virtual logger::Destination
      {
        public:
          DirectFileDestination(const sk::util::Pathname& pathname);
          virtual ~DirectFileDestination();

          void setSize(const sk::util::String& specification);
          void setSize(int size);
          void setBackups(const sk::util::String& specification);
          void setBackups(int backups);

          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
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

          int _size;
          int _backups;
          sk::util::Pathname _pathname;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_DIRECTFILEDESTINATION_ */

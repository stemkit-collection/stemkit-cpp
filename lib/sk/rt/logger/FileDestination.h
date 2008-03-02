/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_FILEDESTINATION_
#define _SK_RT_LOGGER_FILEDESTINATION_

#include <sk/rt/logger/Destination.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination
        : public virtual logger::Destination
      {
        public:
          FileDestination(const sk::util::Pathname& pathname);
          FileDestination(const FileDestination& other);
          virtual ~FileDestination();

          int getSize() const;
          int getBackups() const;

          void setSize(const sk::util::String& specification);
          void setSize(int size);
          void setBackups(const sk::util::String& specification);
          void setBackups(int backups);

          // sk::rt::logger::Destination implementation.
          void dispatch(const char* buffer, int size);
          const std::vector<int> makeReady();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          FileDestination* clone() const;
          
        private:
          FileDestination& operator = (const FileDestination& other);

          void openFile();
          void closeFile();
          void backupFile();
          void initFile();
          bool scanFile();

          int cloneDescriptor() const;
          void writeData(const char* data, int size);
          void writeData(const char* data);

          int _nextBackup;
          off_t _bytesWritten;
          int _descriptor;

          int _size;
          int _backups;
          sk::util::Pathname _pathname;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

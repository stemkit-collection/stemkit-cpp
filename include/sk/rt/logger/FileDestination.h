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

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination
        : public virtual Destination
      {
        public:
          FileDestination(const sk::util::Pathname& pathname);
          virtual ~FileDestination();

          const sk::util::Pathname& getPathname() const;

          void setSize(const sk::util::String& specification);
          void setSize(int size);

          void setBackups(const sk::util::String& specification);
          void setBackups(int backups);

          int getSize() const;
          int getBackups() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
          virtual void makeReady() = 0;

        private:
          FileDestination& operator = (const FileDestination& other);
          
          int _size;
          int _backups;
          sk::util::Pathname _pathname;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_FILEDESTINATION_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTOR_
#define _SK_IO_FILEDESCRIPTOR_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileDescriptor
      : public virtual sk::util::Object 
    {
      public:
        FileDescriptor(int fd);
        FileDescriptor(const FileDescriptor& other);
        virtual ~FileDescriptor();

        int getFileNumber() const;
        
        void close();
        int read(char* buffer, int offset, int length);
        int write(const char* buffer, int offset, int length);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileDescriptor& operator = (const FileDescriptor& other);

        int _fd;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTOR_ */

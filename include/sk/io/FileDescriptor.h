/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTOR_
#define _SK_IO_FILEDESCRIPTOR_

#include <sk/io/LooseFileDescriptor.h>

namespace sk {
  namespace io {
    class FileDescriptor
      : public sk::io::LooseFileDescriptor
    {
      public:
        explicit FileDescriptor(int fd);
        FileDescriptor(const FileDescriptor& other);
        FileDescriptor(const LooseFileDescriptor& other);
        virtual ~FileDescriptor();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTOR_ */

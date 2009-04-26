/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_
#define _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_

#include <sk/io/AbstractOutputStream.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/FileDescriptorProvider.h>

namespace sk {
  namespace io {
    class FileDescriptorOutputStream
      : public AbstractOutputStream,
        public sk::io::FileDescriptorProvider
    {
      public:
        FileDescriptorOutputStream(int fd);
        FileDescriptorOutputStream(const sk::io::FileDescriptor& descriptor);
        FileDescriptorOutputStream(const FileDescriptorOutputStream& other);
        virtual ~FileDescriptorOutputStream();

        // sk::io::FileDescriptorProvider implementation.
        const sk::io::FileDescriptor& getFileDescriptor() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        FileDescriptorOutputStream* clone() const;

        // sk::io::OutputStream implementation.
        int write(const char* buffer, int offset, int length);
        using AbstractOutputStream::write;
        void close();
        
      private:
        FileDescriptorOutputStream& operator = (const FileDescriptorOutputStream& other);

        sk::io::FileDescriptor _descriptor;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_ */

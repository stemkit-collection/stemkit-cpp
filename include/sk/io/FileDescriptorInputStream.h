/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTORINPUTSTREAM_
#define _SK_IO_FILEDESCRIPTORINPUTSTREAM_

#include <sk/io/AbstractInputStream.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/FileDescriptorProvider.h>

namespace sk {
  namespace io {
    class FileDescriptorInputStream
      : public sk::io::AbstractInputStream, 
        public virtual sk::io::FileDescriptorProvider
    {
      public:
        FileDescriptorInputStream(int fd);
        FileDescriptorInputStream(const sk::io::FileDescriptor& descriptor);
        FileDescriptorInputStream(const FileDescriptorInputStream& other);
        virtual ~FileDescriptorInputStream();

        // sk::io::FileDescriptorProvider implementation.
        const sk::io::FileDescriptor& getFileDescriptor() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        FileDescriptorInputStream* clone() const;

        // sk::io::InputStream implementation.
        int read(char* buffer, int offset, int length);
        using sk::io::AbstractInputStream::read;
        void close();
        void inheritable(bool state);
        
      private:
        FileDescriptorInputStream& operator = (const FileDescriptorInputStream& other);

        sk::io::FileDescriptor _descriptor;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORINPUTSTREAM_ */

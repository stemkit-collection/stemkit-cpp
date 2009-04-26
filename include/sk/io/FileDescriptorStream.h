/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_FILEDESCRIPTORSTREAM_H_
#define _SK_IO_FILEDESCRIPTORSTREAM_H_

#include <sk/util/Object.h>
#include <sk/io/Stream.h>
#include <sk/io/FileDescriptorProvider.h>
#include <sk/io/FileDescriptor.h>

namespace sk {
  namespace io {
    class FileDescriptorStream 
      : public virtual sk::io::Stream,
        public virtual sk::io::FileDescriptorProvider
    {
      public:
        FileDescriptorStream(const sk::io::Stream& stream);
        FileDescriptorStream(const FileDescriptorStream& other);
        virtual ~FileDescriptorStream();
    
        // sk::io::Stream implementation.
        virtual void close();
        virtual FileDescriptorStream* clone() const;

        // sk::io::FileDescriptorProvider
        const sk::io::FileDescriptor& getFileDescriptor() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        FileDescriptorStream& operator = (const FileDescriptorStream& other);

        sk::io::FileDescriptor _descriptor;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORSTREAM_H_ */

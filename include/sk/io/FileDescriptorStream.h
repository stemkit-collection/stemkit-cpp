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
#include <sk/util/Holder.hxx>

#include <sk/io/Stream.h>
#include <sk/io/FileDescriptorProvider.h>
#include <sk/io/StreamProvider.h>
#include <sk/io/FileDescriptor.h>

namespace sk {
  namespace io {
    class FileDescriptorStream 
      : public virtual sk::io::Stream,
        public virtual sk::io::FileDescriptorProvider,
        public virtual sk::io::StreamProvider
    {
      public:
        explicit FileDescriptorStream(const int fd);
        explicit FileDescriptorStream(const sk::io::Stream& stream);
        FileDescriptorStream(const FileDescriptorStream& other);
        virtual ~FileDescriptorStream();
    
        // sk::io::Stream implementation.
        void close();
        sk::util::Object* clone() const;
        void inheritable(bool state);

        // sk::io::FileDescriptorProvider implementation.
        const sk::io::FileDescriptor& getFileDescriptor() const;

        // sk::io::StreamProvider implementation.
        sk::io::InputStream& inputStream() const;
        sk::io::OutputStream& outputStream() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        FileDescriptorStream& operator = (const FileDescriptorStream& other);

        sk::io::FileDescriptor _descriptor;
        mutable sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
        mutable sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORSTREAM_H_ */

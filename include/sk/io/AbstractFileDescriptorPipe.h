/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ABSTRACTFILEDESCRIPTORPIPE_
#define _SK_IO_ABSTRACTFILEDESCRIPTORPIPE_

#include <sk/io/Pipe.h>
#include <sk/util/Holder.hxx>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

namespace sk {
  namespace io {
    class FileDescriptor;

    class AbstractFileDescriptorPipe
      : public virtual sk::io::Pipe
    {
      public:
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::Pipe implementation.
        void close();
        void closeInput();
        void closeOutput();
        FileDescriptorInputStream& inputStream() const;
        FileDescriptorOutputStream& outputStream() const;

      protected:
        AbstractFileDescriptorPipe();
        virtual ~AbstractFileDescriptorPipe();

        void setInputFileDescriptor(int fd);
        void setOutputFileDescriptor(int fd);
        void setInputFileDescriptor(const sk::io::FileDescriptor& descriptor);
        void setOutputFileDescriptor(const sk::io::FileDescriptor& descriptor);

      private:
        sk::util::Holder<sk::io::FileDescriptorInputStream> _inputStreamHolder;
        sk::util::Holder<sk::io::FileDescriptorOutputStream> _outputStreamHolder;
    };
  }
}

#endif /* _SK_IO_ABSTRACTFILEDESCRIPTORPIPE_ */

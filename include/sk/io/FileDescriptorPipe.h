/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_FILEDESCRIPTORPIPE_H_
#define _SK_IO_FILEDESCRIPTORPIPE_H_

#include <sk/util/Object.h>
#include <sk/io/AbstractFileDescriptorPipe.h>

namespace sk {
  namespace io {
    class FileDescriptor;

    class FileDescriptorPipe 
      : public sk::io::AbstractFileDescriptorPipe
    {
      public:
        FileDescriptorPipe(const sk::io::FileDescriptor& output, const sk::io::FileDescriptor& input);
        virtual ~FileDescriptorPipe();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        FileDescriptorPipe(const FileDescriptorPipe& other);
        FileDescriptorPipe& operator = (const FileDescriptorPipe& other);
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORPIPE_H_ */

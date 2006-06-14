/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_
#define _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileDescriptorOutputStream
      : public virtual sk::util::Object 
    {
      public:
        FileDescriptorOutputStream();
        virtual ~FileDescriptorOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileDescriptorOutputStream(const FileDescriptorOutputStream& other);
        FileDescriptorOutputStream& operator = (const FileDescriptorOutputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTOROUTPUTSTREAM_ */

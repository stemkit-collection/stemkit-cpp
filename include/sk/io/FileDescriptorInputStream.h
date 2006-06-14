/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEDESCRIPTORINPUTSTREAM_
#define _SK_IO_FILEDESCRIPTORINPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileDescriptorInputStream
      : public virtual sk::util::Object 
    {
      public:
        FileDescriptorInputStream();
        virtual ~FileDescriptorInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileDescriptorInputStream(const FileDescriptorInputStream& other);
        FileDescriptorInputStream& operator = (const FileDescriptorInputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORINPUTSTREAM_ */

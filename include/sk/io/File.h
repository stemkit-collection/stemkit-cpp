/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILE_
#define _SK_IO_FILE_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/io/FileDescriptor.h>

namespace sk {
  namespace io {
    class File
      : public virtual sk::util::Object 
    {
      public:
        File(const sk::util::String& name);
        virtual ~File();

        const sk::util::String getName() const;
        sk::io::FileDescriptor writeDescriptor(bool append = false) const;
        sk::io::FileDescriptor readDescriptor() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        File& operator = (const File& other);

        sk::util::String _name;
    };
  }
}

#endif /* _SK_IO_FILE_ */

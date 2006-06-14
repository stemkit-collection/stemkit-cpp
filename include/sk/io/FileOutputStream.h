/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEOUTPUTSTREAM_
#define _SK_IO_FILEOUTPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileOutputStream
      : public virtual sk::util::Object 
    {
      public:
        FileOutputStream();
        virtual ~FileOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileOutputStream(const FileOutputStream& other);
        FileOutputStream& operator = (const FileOutputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEOUTPUTSTREAM_ */

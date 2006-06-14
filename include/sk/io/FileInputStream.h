/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEINPUTSTREAM_
#define _SK_IO_FILEINPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileInputStream
      : public virtual sk::util::Object 
    {
      public:
        FileInputStream();
        virtual ~FileInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileInputStream(const FileInputStream& other);
        FileInputStream& operator = (const FileInputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEINPUTSTREAM_ */

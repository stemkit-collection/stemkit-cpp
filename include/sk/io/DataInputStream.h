/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAINPUTSTREAM_
#define _SK_IO_DATAINPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class DataInputStream
      : public virtual sk::util::Object 
    {
      public:
        DataInputStream();
        virtual ~DataInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        DataInputStream(const DataInputStream& other);
        DataInputStream& operator = (const DataInputStream& other);
    };
  }
}

#endif /* _SK_IO_DATAINPUTSTREAM_ */

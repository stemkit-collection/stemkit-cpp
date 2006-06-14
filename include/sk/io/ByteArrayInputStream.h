/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BYTEARRAYINPUTSTREAM_
#define _SK_IO_BYTEARRAYINPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class ByteArrayInputStream
      : public virtual sk::util::Object 
    {
      public:
        ByteArrayInputStream();
        virtual ~ByteArrayInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        ByteArrayInputStream(const ByteArrayInputStream& other);
        ByteArrayInputStream& operator = (const ByteArrayInputStream& other);
    };
  }
}

#endif /* _SK_IO_BYTEARRAYINPUTSTREAM_ */

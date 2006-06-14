/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BYTEARRAYOUTPUTSTREAM_
#define _SK_IO_BYTEARRAYOUTPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class ByteArrayOutputStream
      : public virtual sk::util::Object 
    {
      public:
        ByteArrayOutputStream();
        virtual ~ByteArrayOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        ByteArrayOutputStream(const ByteArrayOutputStream& other);
        ByteArrayOutputStream& operator = (const ByteArrayOutputStream& other);
    };
  }
}

#endif /* _SK_IO_BYTEARRAYOUTPUTSTREAM_ */

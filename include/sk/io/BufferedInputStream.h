/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BUFFEREDINPUTSTREAM_
#define _SK_IO_BUFFEREDINPUTSTREAM_

#include <sk/io/DelegatingInputStream.h>

namespace sk {
  namespace io {
    class BufferedInputStream
      : public DelegatingInputStream
    {
      public:
        BufferedInputStream(sk::io::InputStream& stream);
        BufferedInputStream(sk::io::InputStream& stream, int size);
        virtual ~BufferedInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        BufferedInputStream(const BufferedInputStream& other);
        BufferedInputStream& operator = (const BufferedInputStream& other);

        int _size;
    };
  }
}

#endif /* _SK_IO_BUFFEREDINPUTSTREAM_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BUFFEREDINPUTSTREAM_
#define _SK_IO_BUFFEREDINPUTSTREAM_

#include <sk/io/DelegatingInputStream.h>
#include <vector>

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

        // sk::io::InputStream implementation.
        int read(char* buffer, int offset, int size);
        using DelegatingInputStream::read;
        
      private:
        BufferedInputStream(const BufferedInputStream& other);
        BufferedInputStream& operator = (const BufferedInputStream& other);

        int _size;
        int _amount;
        int _offset;
        std::vector<char> _buffer;
        sk::io::InputStream& _stream;
    };
  }
}

#endif /* _SK_IO_BUFFEREDINPUTSTREAM_ */

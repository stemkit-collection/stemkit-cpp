/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BUFFEREDOUTPUTSTREAM_
#define _SK_IO_BUFFEREDOUTPUTSTREAM_

#include <sk/io/DelegatingOutputStream.h>
#include <vector>

namespace sk {
  namespace io {
    class BufferedOutputStream
      : public DelegatingOutputStream
    {
      public:
        BufferedOutputStream(sk::io::OutputStream& stream);
        BufferedOutputStream(sk::io::OutputStream& stream, int size);
        virtual ~BufferedOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::DelegatingOutputStream re-implemenation.
        void flush();
        void close();
        int write(const char* buffer, int offset, int size);
        using DelegatingOutputStream::write;
        
      private:
        BufferedOutputStream(const BufferedOutputStream& other);
        BufferedOutputStream& operator = (const BufferedOutputStream& other);

        void flushChunks(int chunk_size);

        int _size;
        std::vector<char> _buffer;
    };
  }
}

#endif /* _SK_IO_BUFFEREDOUTPUTSTREAM_ */

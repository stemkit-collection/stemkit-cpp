/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BYTEARRAYOUTPUTSTREAM_
#define _SK_IO_BYTEARRAYOUTPUTSTREAM_

#include <sk/io/AbstractOutputStream.h>
#include <vector>

namespace sk {
  namespace io {
    class ByteArrayOutputStream
      : public sk::io::AbstractOutputStream
    {
      public:
        ByteArrayOutputStream(std::vector<char>& buffer);
        virtual ~ByteArrayOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::OutputStream implementation.
        int write(const char* buffer, int offset, int length);
        using AbstractOutputStream::write;
        void close();

      private:
        ByteArrayOutputStream(const ByteArrayOutputStream& other);
        ByteArrayOutputStream& operator = (const ByteArrayOutputStream& other);

        std::vector<char>& _buffer;
        bool _closed;
    };
  }
}

#endif /* _SK_IO_BYTEARRAYOUTPUTSTREAM_ */

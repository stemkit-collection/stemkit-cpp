/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BYTEARRAYINPUTSTREAM_
#define _SK_IO_BYTEARRAYINPUTSTREAM_

#include <sk/io/AbstractInputStream.h>
#include <sk/util/Holder.hxx>
#include <vector>

namespace sk {
  namespace io {
    class ByteArrayInputStream
      : public sk::io::AbstractInputStream
    {
      public:
        ByteArrayInputStream(const char* buffer, int size);
        ByteArrayInputStream(const std::vector<char>& buffer);
        virtual ~ByteArrayInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::InputStream implementation.
        int read(char* buffer, int offset, int length);
        using AbstractInputStream::read;
        void close();
        long long available() const;
        bool markSupported() const;
        int skip(int number);
        void mark(int readlimit);
        void reset();
        void inheritable(bool state);
        
      private:
        ByteArrayInputStream(const ByteArrayInputStream& other);
        ByteArrayInputStream& operator = (const ByteArrayInputStream& other);

        void init();
        void initMark();

        sk::util::Holder<const std::vector<char> > _bufferHolder;
        bool _closed;
        int _cursor;
        int _mark;
        int _markDistance;
    };
  }
}

#endif /* _SK_IO_BYTEARRAYINPUTSTREAM_ */

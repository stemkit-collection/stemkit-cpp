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

        int getByteCount() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::InputStream implementation.
        int read(char* buffer, int offset, int length);
        using AbstractInputStream::read;
        void close();
        uint64_t available() const;
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

        int _depotSize;
        sk::util::Holder<std::vector<char> > _vectorHolder;
        const char* _depot;
        int _depotOffset;
        bool _closed;
        int _mark;
        int _markDistance;
    };
  }
}

#endif /* _SK_IO_BYTEARRAYINPUTSTREAM_ */

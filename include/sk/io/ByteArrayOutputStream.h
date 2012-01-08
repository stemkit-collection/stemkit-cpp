/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_BYTEARRAYOUTPUTSTREAM_
#define _SK_IO_BYTEARRAYOUTPUTSTREAM_

#include <sk/io/AbstractOutputStream.h>
#include <sk/util/Holder.hxx>
#include <vector>

namespace sk {
  namespace io {
    class ByteArrayOutputStream
      : public sk::io::AbstractOutputStream
    {
      public:
        ByteArrayOutputStream(char* buffer, uint64_t size);
        ByteArrayOutputStream(std::vector<char>& buffer);
        virtual ~ByteArrayOutputStream();

        uint64_t getByteCount() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::OutputStream implementation.
        int write(const char* buffer, int offset, int length);
        using AbstractOutputStream::write;
        void close();
        void inheritable(bool state);

      private:
        ByteArrayOutputStream(const ByteArrayOutputStream& other);
        ByteArrayOutputStream& operator = (const ByteArrayOutputStream& other);

        uint64_t _depotSize;
        sk::util::Holder<std::vector<char> > _vectorHolder;
        char* _depot;
        uint64_t _depotOffset;
        bool _closed;
    };
  }
}

#endif /* _SK_IO_BYTEARRAYOUTPUTSTREAM_ */

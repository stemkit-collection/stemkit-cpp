/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_COUNTINGINPUTSTREAM_
#define _SK_IO_COUNTINGINPUTSTREAM_

#include <sk/io/DelegatingInputStream.h>

namespace sk {
  namespace io {
    class CountingInputStream
      : public DelegatingInputStream
    {
      public:
        CountingInputStream(sk::io::InputStream& stream);
        CountingInputStream(sk::io::InputStream* stream);
        virtual ~CountingInputStream();

        uint64_t getByteCount() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::InputStream implementation.
        int read(char* buffer, int offset, int size);
        using DelegatingInputStream::read;

      private:
        CountingInputStream(const CountingInputStream& other);
        CountingInputStream& operator = (const CountingInputStream& other);

        uint64_t _byteCount;
    };
  }
}

#endif /* _SK_IO_COUNTINGINPUTSTREAM_ */

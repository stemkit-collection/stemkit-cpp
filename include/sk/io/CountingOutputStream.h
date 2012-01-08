/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_COUNTINGOUTPUTSTREAM_H_
#define _SK_IO_COUNTINGOUTPUTSTREAM_H_

#include <sk/io/DelegatingOutputStream.h>

namespace sk {
  namespace io {
    class CountingOutputStream
      : public DelegatingOutputStream
    {
      public:
        CountingOutputStream(sk::io::OutputStream& stream);
        CountingOutputStream(sk::io::OutputStream* stream);
        virtual ~CountingOutputStream();

        uint64_t getByteCount() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::DelegatingOutputStream re-implemenation.
        int write(const char* buffer, int offset, int size);
        using DelegatingOutputStream::write;

      private:
        CountingOutputStream(const CountingOutputStream& other);
        CountingOutputStream& operator = (const CountingOutputStream& other);

        uint64_t _byteCount;
    };
  }
}

#endif /* _SK_IO_COUNTINGOUTPUTSTREAM_H_ */

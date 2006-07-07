/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DELEGATINGINPUTSTREAM_
#define _SK_IO_DELEGATINGINPUTSTREAM_

#include <sk/io/AbstractInputStream.h>

namespace sk {
  namespace io {
    class DelegatingInputStream
      : public virtual sk::io::AbstractInputStream
    {
      public:
        DelegatingInputStream(sk::io::InputStream& stream);
        virtual ~DelegatingInputStream();

        sk::io::InputStream& getInputStream() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::InputStream implementation.
        void close();
        int skip(int number);
        long long available() const;
        bool markSupported() const;
        void mark(int readlimit);
        void reset();
        int read(char* buffer, int offset, int length);
        using AbstractInputStream::read;
        
      private:
        DelegatingInputStream(const DelegatingInputStream& other);
        DelegatingInputStream& operator = (const DelegatingInputStream& other);

        sk::io::InputStream& _stream;
    };
  }
}

#endif /* _SK_IO_DELEGATINGINPUTSTREAM_ */

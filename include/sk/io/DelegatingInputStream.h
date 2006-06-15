/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DELEGATINGINPUTSTREAM_
#define _SK_IO_DELEGATINGINPUTSTREAM_

#include <sk/io/InputStream.h>

namespace sk {
  namespace io {
    class DelegatingInputStream
      : public virtual sk::io::InputStream
    {
      public:
        DelegatingInputStream(sk::io::InputStream& stream);
        virtual ~DelegatingInputStream();

        sk::io::InputStream& getInputStream() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::InputStream implementation.
        char read();
        int read(char* buffer, int offset, int length);
        std::vector<char> read(int number);
        std::vector<char>& read(std::vector<char>& buffer, int number);
        void close();
        int skip(int number);
        int available() const;
        bool markSupported() const;
        void mark(int readlimit);
        void reset();
        
      private:
        DelegatingInputStream(const DelegatingInputStream& other);
        DelegatingInputStream& operator = (const DelegatingInputStream& other);

        sk::io::InputStream& _stream;
    };
  }
}

#endif /* _SK_IO_DELEGATINGINPUTSTREAM_ */

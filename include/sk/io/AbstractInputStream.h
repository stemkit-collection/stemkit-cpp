/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ABSTRACTINPUTSTREAM_
#define _SK_IO_ABSTRACTINPUTSTREAM_

#include <sk/io/InputStream.h>

namespace sk {
  namespace io {
    /** This class provides default some of the sk::io::InputStream 
     *  operations as well as implements different flavours of read()
     *  via the basic one (still abstract).
    */
    class AbstractInputStream
      : public virtual sk::io::InputStream
    {
      public:
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        sk::util::Object* clone() const;

        // sk::io::InputStream implementation.
        virtual int read(char* buffer, int offset, int length) = 0;
        char read();
        std::vector<char> read(int number);
        std::vector<char>& read(std::vector<char>& buffer, int number);
        int skip(int number);
        long long available() const;
        bool markSupported() const;
        void mark(int readlimit);
        void reset();

      protected:
        int filterReadEvents(int n);
    };
  }
}

#endif /* _SK_IO_ABSTRACTINPUTSTREAM_ */

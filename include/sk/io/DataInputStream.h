/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAINPUTSTREAM_
#define _SK_IO_DATAINPUTSTREAM_

#include <sk/io/DelegatingInputStream.h>
#include <sk/io/DataInput.h>

namespace sk {
  namespace io {
    class DataInputStream
      : public sk::io::DelegatingInputStream,
        public virtual sk::io::DataInput
    {
      public:
        DataInputStream(sk::io::InputStream& stream);
        virtual ~DataInputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::DataInput implementation.
        int readInt();
        long long readLong();
        short readShort();
        char readChar();
        double readDouble();
        float readFloat();
        int skipBytes(int number);
        const sk::util::String readLine();
        std::vector<char>& readFully(std::vector<char>& buffer, int number);
        std::vector<char> readFully(int number);

      private:
        DataInputStream(const DataInputStream& other);
        DataInputStream& operator = (const DataInputStream& other);
    };
  }
}

#endif /* _SK_IO_DATAINPUTSTREAM_ */

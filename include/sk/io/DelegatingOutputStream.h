/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DELEGATINGOUTPUTSTREAM_
#define _SK_IO_DELEGATINGOUTPUTSTREAM_

#include <sk/io/OutputStream.h>

namespace sk {
  namespace io {
    class DelegatingOutputStream
      : public virtual sk::io::OutputStream
    {
      public:
        DelegatingOutputStream(sk::io::OutputStream& stream);
        virtual ~DelegatingOutputStream();

        sk::io::OutputStream& getOutputStream() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::OutputSteam implementation.
        void close();
        void flush();
        int write(const char* buffer, int offset, int length);
        int write(const std::vector<char>& data, int offset);
        int write(const std::vector<char>& data);
        int write(char byte);
      private:
        DelegatingOutputStream(const DelegatingOutputStream& other);
        DelegatingOutputStream& operator = (const DelegatingOutputStream& other);

        sk::io::OutputStream& _stream;
    };
  }
}

#endif /* _SK_IO_DELEGATINGOUTPUTSTREAM_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_OUTPUTSTREAM_
#define _SK_IO_OUTPUTSTREAM_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace io {
    class OutputStream
      : public virtual sk::util::Object 
    {
      public:
        /// Closes this output stream and releases any system resources
        /// associated with this stream.
        virtual void close() = 0;

        /// Flushes this output stream and forces any buffered output bytes 
        /// to be written out.
        virtual void flush() = 0;

        /// Writes length bytes from the specified byte array starting from
        /// offset to this stream. Returns the number of bytes written to 
        /// this stream.
        virtual int write(const char* buffer, int offset, int length) = 0;

        /// Writes length bytes from the specified vector of chars starting
        /// from offset to this stream. Returns the number of bytes written 
        /// to this stream.
        virtual int write(const std::vector<char>& data, int offset) = 0;

        /// Writes length bytes from the specified vector of chars to this 
        /// stream. Returns the number of bytes written to this stream.
        virtual int write(const std::vector<char>& data) = 0;

        /// Writes the specified byte to this output stream.
        virtual int write(char byte) = 0;
    };
  }
}

#endif /* _SK_IO_OUTPUTSTREAM_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_INPUTSTREAM_
#define _SK_IO_INPUTSTREAM_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace io {
    class InputStream
      : public virtual sk::util::Object 
    {
      public:
        /// Reads the next byte of data from the input stream.
        virtual char read() = 0;
        
        /// Reads up to lenght bytes of data from the input stream into an 
        /// array of bytes starting from offset.
        virtual int read(char* buffer, int offset, int length) = 0;

        /// Reads up to number bytes of data from the input stream and 
        /// returns them as a vector of chars.
        virtual std::vector<char> read(int number) = 0;
        
        /// Reads up to number bytes of data from the input stream into the
        /// specified vector of chars. The vector size will be adjusted
        /// depending on the actual amount of date read. Returns a reference 
        /// to the same vectory.
        virtual std::vector<char>& read(std::vector<char>& buffer, int number) = 0;
        
        /// Closes this input stream and releases any system resources
        /// associated with the stream.
        virtual void close() = 0;

        /// Skips over and discards n bytes of data from this input stream.
        virtual int skip(int number) = 0;

        /// Returns the number of bytes that can be read (or skipped over)
        /// from this input stream without blocking by the next caller of a
        /// method for this input stream.
        virtual long long available() const = 0;
        
        /// Tests if this input stream supports the mark and reset methods.
        virtual bool markSupported() const = 0;

        /// Marks the current position in this input stream.
        virtual void mark(int readlimit) = 0;

        /// Repositions this stream to the position at the time the mark
        /// method was last called on this input stream.
        virtual void reset() = 0;

        /// Instantiates another object of the same class as a copy 
        /// of itself.
        virtual InputStream* clone() const = 0;
    };
  }
}

#endif /* _SK_IO_INPUTSTREAM_ */

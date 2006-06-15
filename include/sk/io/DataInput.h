/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAINPUT_
#define _SK_IO_DATAINPUT_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace io {
    class DataInput
      : public virtual sk::util::Object 
    {
      public:
        /// Reads four input bytes and returns an int value.
        virtual int readInt() = 0;

        /// Reads eight input bytes and returns a long long value.
        virtual long long readLong() = 0;

        /// Reads two input bytes and returns a short value.
        virtual short readShort() = 0;

        /// Reads an input char and returns the char value.
        virtual char readChar() = 0;

        /// Reads eight input bytes and returns a double value.
        virtual double readDouble() = 0;

        /// Reads four input bytes and returns a float value.
        virtual float readFloat() = 0;

        /// Makes an attempt to skip over n bytes of data from the input
        /// stream, discarding the skipped bytes.
        virtual int skipBytes(int number) = 0;

        /// Reads the next line of text from the input stream.
        virtual const sk::util::String readLine() = 0;

        /// Reads exactly number input bytes and stores them in the specified
        /// vector of chars. Blocks if the data is not yet available. Returns
        /// a reference to the same vector.
        virtual std::vector<char>& readFully(std::vector<char>& buffer, int number) = 0;

        /// Reads exactly number input bytes and returns them as a vector of chars. 
        /// Blocks if the data is not yet available.
        virtual std::vector<char> readFully(int number) = 0;
    };
  }
}

#endif /* _SK_IO_DATAINPUT_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAOUTPUT_
#define _SK_IO_DATAOUTPUT_

#include <sk/util/Object.h>
#include <vector>
#include <string>

namespace sk {
  namespace io {
    class DataOutput
      : public virtual sk::util::Object 
    {
      public:
        /// Writes an int value, which is comprised of four bytes, to the
        /// output stream.
        virtual void writeInt(int value) = 0;

        /// Writes a long value, which is comprised of eight bytes, to the
        /// output stream.
        virtual void writeLong(long long value) = 0;

        /// Writes two bytes to the output stream to represent the value of
        /// the argument.
        virtual void writeShort(short value) = 0;

        /// Writes a double value, which is comprised of eight bytes, to the
        /// output stream.
        virtual void writeDouble(double value) = 0;

        /// Writes a float value, which is comprised of four bytes, to the
        /// output stream.
        virtual void writeFloat(float value) = 0;

        /// Writes to the output stream the eight low- order bits of the
        /// argument.
        virtual void writeChar(char value) = 0;

        /// Writes a string to the output stream.
        virtual void writeChars(const std::string& value) = 0;

        /// Writes to the output stream all the bytes of the vector.
        virtual void writeFully(const std::vector<char>& value) = 0;
    };
  }
}

#endif /* _SK_IO_DATAOUTPUT_ */

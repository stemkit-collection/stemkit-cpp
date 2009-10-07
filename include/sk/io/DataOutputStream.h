/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
e*  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAOUTPUTSTREAM_
#define _SK_IO_DATAOUTPUTSTREAM_

#include <sk/util/Holder.hxx>
#include <sk/io/DelegatingOutputStream.h>
#include <sk/io/DataOutput.h>

namespace sk {
  namespace io {
    class DataOutputStream
      : public DelegatingOutputStream,
        public virtual sk::io::DataOutput
    {
      public:
        DataOutputStream(sk::io::OutputStream& stream);
        virtual ~DataOutputStream();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        void writeInt(int value);
        void writeLong(long long value);
        void writeShort(short value);
        void writeDouble(double value);
        void writeFloat(float value);
        void writeChar(char value);
        void writeChars(const std::string& value);
        void writeFully(const std::vector<char>& value);
        void writeFully(const char* buffer, int length);

      private:
        DataOutputStream(const DataOutputStream& other);
        DataOutputStream& operator = (const DataOutputStream& other);
    };
  }
}

#endif /* _SK_IO_DATAOUTPUTSTREAM_ */

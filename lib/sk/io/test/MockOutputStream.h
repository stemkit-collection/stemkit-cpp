/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_MOCKOUTPUTSTREAM_
#define _SK_IO_TEST_MOCKOUTPUTSTREAM_

#include <sk/io/AbstractOutputStream.h>
#include <sk/util/Container.h>

namespace sk {
  namespace io {
    namespace test {
      class MockOutputStream
        : public sk::io::AbstractOutputStream
      {
        public:
          MockOutputStream();
          virtual ~MockOutputStream();

          int closeCounter() const;
          int flushCounter() const;
          int chunks() const;
          const sk::util::Container chunk(int index) const;
          int dataSize() const;
          const sk::util::Container data() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::io::OutputStream implementation.
          void close();
          void flush();
          int write(const char* buffer, int offset, int size);
          using AbstractOutputStream::write;
          
        private:
          MockOutputStream(const MockOutputStream& other);
          MockOutputStream& operator = (const MockOutputStream& other);

          bool _closeCounter;
          bool _flushCounter;
          std::vector<sk::util::Container> _dataChunks;
      };
    }
  }
}

#endif /* _SK_IO_TEST_MOCKOUTPUTSTREAM_ */

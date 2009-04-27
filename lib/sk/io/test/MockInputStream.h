/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_MOCKINPUTSTREAM_
#define _SK_IO_TEST_MOCKINPUTSTREAM_

#include <sk/io/AbstractInputStream.h>
#include <sk/util/Container.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace io {
    class InputStream;

    namespace test {
      class MockInputStream
        : public AbstractInputStream
      {
        public:
          MockInputStream();
          virtual ~MockInputStream();

          int closeCounter() const;
          int chunks() const;
          const sk::util::Container chunk(int index) const;
          void setData(const sk::util::Container& container);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::io::InputStream implementation.
          void close();
          int read(char* buffer, int offset, int size);
          using AbstractInputStream::read;
          void inheritable(bool state);
          
        private:
          MockInputStream(const MockInputStream& other);
          MockInputStream& operator = (const MockInputStream& other);

          int _closeCounter;
          sk::util::Container _data;
          std::vector<sk::util::Container> _chunks;
          sk::util::Holder<InputStream> _streamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_MOCKINPUTSTREAM_ */

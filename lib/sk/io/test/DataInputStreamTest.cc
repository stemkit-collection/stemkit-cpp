/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "DataInputStreamTest.h"
#include <sk/io/DataInputStream.h>
#include <sk/io/ByteArrayInputStream.h>
#include <sk/io/EOFException.h>
#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::DataInputStreamTest);

sk::io::test::DataInputStreamTest::
DataInputStreamTest()
{
}

sk::io::test::DataInputStreamTest::
~DataInputStreamTest()
{
}

void
sk::io::test::DataInputStreamTest::
setUp()
{
  _bufferHolder.set(new std::vector<char>());
  _inputStreamHolder.set(new sk::io::ByteArrayInputStream(_bufferHolder.get()));
  _dataStreamHolder.set(new sk::io::DataInputStream(_inputStreamHolder.getMutable()));
}

void
sk::io::test::DataInputStreamTest::
tearDown()
{
  _dataStreamHolder.clear();
  _inputStreamHolder.clear();
  _bufferHolder.clear();
}

void
sk::io::test::DataInputStreamTest::
testReadFromEmpty()
{
  CPPUNIT_ASSERT_THROW(stream().readChar(), sk::io::EOFException);
  CPPUNIT_ASSERT_THROW(stream().readLine(), sk::io::EOFException);
  CPPUNIT_ASSERT_THROW(stream().readInt(), sk::io::EOFException);

  CPPUNIT_ASSERT_EQUAL(0, stream().skipBytes(10));
}

void
sk::io::test::DataInputStreamTest::
testReadChar()
{
  buffer().push_back('z');
  buffer().push_back('v');

  CPPUNIT_ASSERT_EQUAL('z', stream().readChar());
  CPPUNIT_ASSERT_EQUAL('v', stream().readChar());

  CPPUNIT_ASSERT_THROW(stream().readChar(), sk::io::EOFException);
}

void
sk::io::test::DataInputStreamTest::
testReadLine()
{
  buffer() = sk::util::Container("Hello, world!!!\nhe-he");

  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello, world!!!\n"), stream().readLine());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("he-he").inspect(), stream().readLine().inspect());
  CPPUNIT_ASSERT_THROW(stream().readLine(), sk::io::EOFException);
}

void
sk::io::test::DataInputStreamTest::
testReadInt()
{
  uint32_t v1 = 0x245;
  uint32_t v2 = 0x1ab12;

  const char* data = reinterpret_cast<const char*>(&v1);

  buffer().push_back(*(data + 0));
  buffer().push_back(*(data + 1));
  buffer().push_back(*(data + 2));
  buffer().push_back(*(data + 3));

  data = reinterpret_cast<const char*>(&v2);

  buffer().push_back(*(data + 0));
  buffer().push_back(*(data + 1));
  buffer().push_back(*(data + 2));
  buffer().push_back(*(data + 3));

  buffer().push_back(0);
  buffer().push_back(0);
  buffer().push_back(0);

  CPPUNIT_ASSERT_EQUAL(v1, stream().readInt());
  CPPUNIT_ASSERT_EQUAL(v2, stream().readInt());

  CPPUNIT_ASSERT_THROW(stream().readInt(), sk::io::EOFException);
}

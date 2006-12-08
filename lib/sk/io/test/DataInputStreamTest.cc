/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
  _dataStreamHolder.set(new sk::io::DataInputStream(_inputStreamHolder.get()));
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
  buffer().push_back('\x45');
  buffer().push_back('\x02');
  buffer().push_back('\x00');
  buffer().push_back('\x00');

  buffer().push_back('\x12');
  buffer().push_back('\xAB');
  buffer().push_back('\x01');
  buffer().push_back('\x00');

  buffer().push_back('\x00');
  buffer().push_back('\x00');
  buffer().push_back('\x00');

  CPPUNIT_ASSERT_EQUAL(0x245, stream().readInt());
  CPPUNIT_ASSERT_EQUAL(0x1AB12, stream().readInt());

  CPPUNIT_ASSERT_THROW(stream().readInt(), sk::io::EOFException);
}

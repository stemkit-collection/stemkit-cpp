/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "DataOutputStreamTest.h"
#include <sk/io/DataOutputStream.h>
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/util/inspect.h>
#include <sk/util/Holder.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::DataOutputStreamTest);

sk::io::test::DataOutputStreamTest::
DataOutputStreamTest()
{
}

sk::io::test::DataOutputStreamTest::
~DataOutputStreamTest()
{
}

void
sk::io::test::DataOutputStreamTest::
setUp()
{
  _bufferHolder.set(new std::vector<char>());
  _outputStreamHolder.set(new ByteArrayOutputStream(_bufferHolder.getMutable()));
  _dataStreamHolder.set(new DataOutputStream(_outputStreamHolder.getMutable()));
}

void
sk::io::test::DataOutputStreamTest::
tearDown()
{
  _dataStreamHolder.clear();
  _outputStreamHolder.clear();
  _bufferHolder.clear();
}

void
sk::io::test::DataOutputStreamTest::
testWriteChar()
{
  stream().writeChar('c');
  stream().writeChar('b');
  stream().writeChar('a');

  CPPUNIT_ASSERT_EQUAL(3, int(buffer().size()));
  CPPUNIT_ASSERT_EQUAL('c', buffer()[0]);
  CPPUNIT_ASSERT_EQUAL('b', buffer()[1]);
  CPPUNIT_ASSERT_EQUAL('a', buffer()[2]);

}

void
sk::io::test::DataOutputStreamTest::
testWriteChars()
{
  stream().writeChars("hello");

  CPPUNIT_ASSERT_EQUAL(5, int(buffer().size()));
  CPPUNIT_ASSERT_EQUAL('h', buffer()[0]);
  CPPUNIT_ASSERT_EQUAL('e', buffer()[1]);
  CPPUNIT_ASSERT_EQUAL('l', buffer()[2]);
  CPPUNIT_ASSERT_EQUAL('l', buffer()[3]);
  CPPUNIT_ASSERT_EQUAL('o', buffer()[4]);
}

void
sk::io::test::DataOutputStreamTest::
testWriteInt()
{
  int value = 0x4fa;
  const char* data = reinterpret_cast<const char*>(&value);

  stream().writeInt(value);
  CPPUNIT_ASSERT_EQUAL(size_t(4), buffer().size());

  CPPUNIT_ASSERT_EQUAL(*(data + 0), buffer()[0]);
  CPPUNIT_ASSERT_EQUAL(*(data + 1), buffer()[1]);
  CPPUNIT_ASSERT_EQUAL(*(data + 2), buffer()[2]);
  CPPUNIT_ASSERT_EQUAL(*(data + 3), buffer()[3]);

  value = 15;
  data = reinterpret_cast<const char*>(&value);

  stream().writeInt(value);
  CPPUNIT_ASSERT_EQUAL(size_t(8), buffer().size());

  CPPUNIT_ASSERT_EQUAL(*(data + 0), buffer()[4]);
  CPPUNIT_ASSERT_EQUAL(*(data + 1), buffer()[5]);
  CPPUNIT_ASSERT_EQUAL(*(data + 2), buffer()[6]);
  CPPUNIT_ASSERT_EQUAL(*(data + 3), buffer()[7]);
}

void
sk::io::test::DataOutputStreamTest::
testWriteContainer()
{
  stream().writeFully(sk::util::Container(""));
  stream().writeFully(sk::util::Container("hello"));
  stream().writeFully(sk::util::Container(""));

  CPPUNIT_ASSERT_EQUAL(5, int(buffer().size()));
  CPPUNIT_ASSERT_EQUAL('h', buffer()[0]);
  CPPUNIT_ASSERT_EQUAL('e', buffer()[1]);
  CPPUNIT_ASSERT_EQUAL('l', buffer()[2]);
  CPPUNIT_ASSERT_EQUAL('l', buffer()[3]);
  CPPUNIT_ASSERT_EQUAL('o', buffer()[4]);
}


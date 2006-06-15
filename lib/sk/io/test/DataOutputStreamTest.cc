/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "DataOutputStreamTest.h"
#include <sk/io/DataOutputStream.h>
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/util/inspect.h>

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
  _outputStreamHolder.set(new ByteArrayOutputStream(_bufferHolder.get()));
  _dataStreamHolder.set(new DataOutputStream(_outputStreamHolder.get()));
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
  stream().writeInt(0x4fa);
  CPPUNIT_ASSERT_EQUAL(4, int(buffer().size()));

  CPPUNIT_ASSERT_EQUAL('\xFA', buffer()[0]);
  CPPUNIT_ASSERT_EQUAL('\x04', buffer()[1]);
  CPPUNIT_ASSERT_EQUAL('\x00', buffer()[2]);
  CPPUNIT_ASSERT_EQUAL('\x00', buffer()[3]);

  stream().writeInt(15);
  CPPUNIT_ASSERT_EQUAL(8, int(buffer().size()));

  CPPUNIT_ASSERT_EQUAL('\x0F', buffer()[4]);
  CPPUNIT_ASSERT_EQUAL('\x00', buffer()[5]);
  CPPUNIT_ASSERT_EQUAL('\x00', buffer()[6]);
  CPPUNIT_ASSERT_EQUAL('\x00', buffer()[7]);

}

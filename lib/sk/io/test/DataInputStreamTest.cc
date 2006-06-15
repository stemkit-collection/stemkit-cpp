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
}

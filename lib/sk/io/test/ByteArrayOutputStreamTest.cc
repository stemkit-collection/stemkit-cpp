/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ByteArrayOutputStreamTest.h"
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/IOException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::ByteArrayOutputStreamTest);

sk::io::test::ByteArrayOutputStreamTest::
ByteArrayOutputStreamTest()
{
}

sk::io::test::ByteArrayOutputStreamTest::
~ByteArrayOutputStreamTest()
{
}

void
sk::io::test::ByteArrayOutputStreamTest::
setUp()
{
}

void
sk::io::test::ByteArrayOutputStreamTest::
tearDown()
{
}

void
sk::io::test::ByteArrayOutputStreamTest::
testWriteSequential()
{
  std::vector<char> data;
  sk::io::ByteArrayOutputStream stream(data);

  CPPUNIT_ASSERT_EQUAL(0, int(data.size()));

  stream.write('a');
  stream.write('b');
  stream.write('c');

  CPPUNIT_ASSERT_EQUAL(3, int(data.size()));
  stream.close();

  CPPUNIT_ASSERT_EQUAL('a', data[0]);
  CPPUNIT_ASSERT_EQUAL('b', data[1]);
  CPPUNIT_ASSERT_EQUAL('c', data[2]);

  CPPUNIT_ASSERT_THROW(stream.write('z'), sk::io::IOException);
}

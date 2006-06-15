/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ByteArrayInputStreamTest.h"
#include <sk/io/ByteArrayInputStream.h>
#include <sk/io/EOFException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::ByteArrayInputStreamTest);

sk::io::test::ByteArrayInputStreamTest::
ByteArrayInputStreamTest()
{
}

sk::io::test::ByteArrayInputStreamTest::
~ByteArrayInputStreamTest()
{
}

void
sk::io::test::ByteArrayInputStreamTest::
setUp()
{
}

void
sk::io::test::ByteArrayInputStreamTest::
tearDown()
{
}

void
sk::io::test::ByteArrayInputStreamTest::
testEmpty()
{
  sk::io::ByteArrayInputStream stream(0, 0);

  CPPUNIT_ASSERT_EQUAL(0, stream.available());
  CPPUNIT_ASSERT_THROW(stream.read(), sk::io::EOFException);
}

void
sk::io::test::ByteArrayInputStreamTest::
testReadOneByOne()
{
  char* data = "abc";
  sk::io::ByteArrayInputStream stream(data, 4);

  CPPUNIT_ASSERT_EQUAL(4, stream.available());
  CPPUNIT_ASSERT_EQUAL('a', stream.read());
  CPPUNIT_ASSERT_EQUAL('b', stream.read());
  CPPUNIT_ASSERT_EQUAL('c', stream.read());
  CPPUNIT_ASSERT_EQUAL(char(0), stream.read());

  CPPUNIT_ASSERT_EQUAL(0, stream.available());
  CPPUNIT_ASSERT_THROW(stream.read(), sk::io::EOFException);
}

void
sk::io::test::ByteArrayInputStreamTest::
testReadByVector()
{
  char* data = "abcdefg";
  sk::io::ByteArrayInputStream stream(data, strlen(data));

  CPPUNIT_ASSERT_EQUAL(7, stream.available());

  const std::vector<char>& chunk1 = stream.read(4);
  CPPUNIT_ASSERT_EQUAL(3, stream.available());
  CPPUNIT_ASSERT_EQUAL(4, int(chunk1.size()));

  CPPUNIT_ASSERT_EQUAL('a', chunk1[0]);
  CPPUNIT_ASSERT_EQUAL('b', chunk1[1]);
  CPPUNIT_ASSERT_EQUAL('c', chunk1[2]);
  CPPUNIT_ASSERT_EQUAL('d', chunk1[3]);

  const std::vector<char>& chunk2 = stream.read(10);
  CPPUNIT_ASSERT_EQUAL(0, stream.available());
  CPPUNIT_ASSERT_EQUAL(3, int(chunk2.size()));

  CPPUNIT_ASSERT_EQUAL('e', chunk2[0]);
  CPPUNIT_ASSERT_EQUAL('f', chunk2[1]);
  CPPUNIT_ASSERT_EQUAL('g', chunk2[2]);

  CPPUNIT_ASSERT_THROW(stream.read(), sk::io::EOFException);
}

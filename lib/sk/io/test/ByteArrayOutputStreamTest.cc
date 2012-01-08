/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ByteArrayOutputStreamTest.h"
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <sk/util/Container.h>

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
testWriteToContainer()
{
  sk::util::Container data;
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
  CPPUNIT_ASSERT_EQUAL(uint64_t(3), stream.getByteCount());
}

void
sk::io::test::ByteArrayOutputStreamTest::
testWriteToCharBuffer()
{
  char data[10] = { 0 };
  CPPUNIT_ASSERT_EQUAL(sk::util::Container("\0\0\0\0\0\0\0\0\0\0", 10).inspect(), sk::util::Container(data, sizeof(data)).inspect());
  sk::io::ByteArrayOutputStream stream(data, sizeof(data));
  stream.write('a');
  stream.write('b');
  stream.write('c');

  CPPUNIT_ASSERT_EQUAL(sk::util::Container("abc\0\0\0\0\0\0\0", 10).inspect(), sk::util::Container(data, sizeof(data)).inspect());
  stream.write("zzz", 0, 4);
  stream.write('u');

  CPPUNIT_ASSERT_EQUAL(sk::util::Container("abczzz\0u\0\0", 10).inspect(), sk::util::Container(data, sizeof(data)).inspect());
  CPPUNIT_ASSERT_EQUAL(uint64_t(8), stream.getByteCount());

  CPPUNIT_ASSERT_THROW(stream.write("hello", 0, 5), sk::io::EOFException);
  CPPUNIT_ASSERT_EQUAL(sk::util::Container("abczzz\0uhe", 10).inspect(), sk::util::Container(data, sizeof(data)).inspect());
  CPPUNIT_ASSERT_EQUAL(uint64_t(10), stream.getByteCount());
}

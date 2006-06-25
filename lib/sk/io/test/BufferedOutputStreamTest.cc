/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "BufferedOutputStreamTest.h"
#include <sk/util/Holder.cxx>
#include <sk/io/BufferedOutputStream.h>
#include "MockOutputStream.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::BufferedOutputStreamTest);

sk::io::test::BufferedOutputStreamTest::
BufferedOutputStreamTest()
{
}

sk::io::test::BufferedOutputStreamTest::
~BufferedOutputStreamTest()
{
}

void
sk::io::test::BufferedOutputStreamTest::
setUp()
{
  _mockHolder.set(new MockOutputStream());
  _streamHolder.set(new BufferedOutputStream(mock()));
}

void
sk::io::test::BufferedOutputStreamTest::
tearDown()
{
  _streamHolder.clear();
  _mockHolder.clear();
}

void
sk::io::test::BufferedOutputStreamTest::
testBuffer()
{
  _streamHolder.set(new BufferedOutputStream(mock(), 12));

  stream().write(sk::util::Container("abcdefg"));
  CPPUNIT_ASSERT_EQUAL(0, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(0, mock().dataSize());
  stream().write(sk::util::Container("xxxxx"));
  CPPUNIT_ASSERT_EQUAL(1, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(12, mock().dataSize());
  stream().write('z');

  CPPUNIT_ASSERT_EQUAL(12, mock().dataSize());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxx").inspect(), mock().data().inspect());

  stream().write('z');
  stream().flush();

  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(14, mock().dataSize());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxxzz").inspect(), mock().data().inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testFlushOnClose()
{
  stream().write(sk::util::Container("abcdefg"));
  CPPUNIT_ASSERT_EQUAL(0, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(0, mock().dataSize());

  stream().close();

  CPPUNIT_ASSERT_EQUAL(1, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(7, mock().dataSize());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefg").inspect(), mock().data().inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testWriteLargerChunk()
{
  _streamHolder.set(new BufferedOutputStream(mock(), 4));
  stream().write(sk::util::Container("123412345"));
  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(8, mock().dataSize());
}

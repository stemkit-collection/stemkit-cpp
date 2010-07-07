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

  CPPUNIT_ASSERT_EQUAL(7, stream().write(sk::util::Container("abcdefg")));

  CPPUNIT_ASSERT_EQUAL(0, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(0, mock().dataSize());

  CPPUNIT_ASSERT_EQUAL(5, stream().write(sk::util::Container("xxxxx")));

  CPPUNIT_ASSERT_EQUAL(1, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(12, mock().dataSize());

  CPPUNIT_ASSERT_EQUAL(1, stream().write('z'));

  CPPUNIT_ASSERT_EQUAL(12, mock().dataSize());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxx").inspect(), mock().data().inspect());

  CPPUNIT_ASSERT_EQUAL(1, stream().write('z'));
  stream().flush();

  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(14, mock().dataSize());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxxzz").inspect(), mock().data().inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testFlushOnClose()
{
  CPPUNIT_ASSERT_EQUAL(7, stream().write(sk::util::Container("abcdefg")));
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

  CPPUNIT_ASSERT_EQUAL(10, stream().write(sk::util::Container("1234567890")));
  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(8, mock().dataSize());
  stream().flush();
  CPPUNIT_ASSERT_EQUAL(3, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("1234").inspect(), mock().chunk(0).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("5678").inspect(), mock().chunk(1).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("90").inspect(), mock().chunk(2).inspect());
}

void 
sk::io::test::BufferedOutputStreamTest::
testNoBuffer()
{
  _streamHolder.set(new BufferedOutputStream(mock(), 1));
  mock().setDataLimit(3);

  CPPUNIT_ASSERT_EQUAL(7, stream().write(sk::util::Container("abcdefg")));
  CPPUNIT_ASSERT_EQUAL(7, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefg").inspect(), mock().data().inspect());

  stream().flush();
  CPPUNIT_ASSERT_EQUAL(7, mock().chunks());
}

void
sk::io::test::BufferedOutputStreamTest::
testBufferLimitedWrite()
{
  _streamHolder.set(new BufferedOutputStream(mock(), 5));
  mock().setDataLimit(3);

  CPPUNIT_ASSERT_EQUAL(7, stream().write(sk::util::Container("abcdefg")));
  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(3, mock().chunk(0).size());
  CPPUNIT_ASSERT_EQUAL(2, mock().chunk(1).size());

  stream().write('z');
  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  stream().flush();
  CPPUNIT_ASSERT_EQUAL(3, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(2, mock().chunk(1).size());
  CPPUNIT_ASSERT_EQUAL(3, mock().chunk(2).size());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("abc").inspect(), mock().chunk(0).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("de").inspect(), mock().chunk(1).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("fgz").inspect(), mock().chunk(2).inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testZeroWrite()
{
  CPPUNIT_ASSERT_EQUAL(0, stream().write("", 0, 0));
  stream().flush();

  CPPUNIT_ASSERT_EQUAL(0, mock().chunks());
}

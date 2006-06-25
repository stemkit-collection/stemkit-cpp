/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "BufferedOutputStreamTest.h"
#include <sk/util/Holder.cxx>
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/BufferedOutputStream.h>

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
  _containerHolder.set(new sk::util::Container());
  _outputHolder.set(new ByteArrayOutputStream(container()));
  _streamHolder.set(new BufferedOutputStream(output()));
}

void
sk::io::test::BufferedOutputStreamTest::
tearDown()
{
  _streamHolder.clear();
  _outputHolder.clear();
  _containerHolder.clear();
}

void
sk::io::test::BufferedOutputStreamTest::
testBuffer()
{
  _streamHolder.set(new BufferedOutputStream(output(), 12));

  stream().write(sk::util::Container("abcdefg"));
  CPPUNIT_ASSERT_EQUAL(0, container().size());
  stream().write(sk::util::Container("xxxxx"));
  CPPUNIT_ASSERT_EQUAL(12, container().size());
  stream().write('z');

  CPPUNIT_ASSERT_EQUAL(12, container().size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxx").inspect(), container().inspect());

  stream().write('z');
  stream().flush();

  CPPUNIT_ASSERT_EQUAL(14, container().size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefgxxxxxzz").inspect(), container().inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testFlushOnClose()
{
  stream().write(sk::util::Container("abcdefg"));
  CPPUNIT_ASSERT_EQUAL(0, container().size());

  stream().close();

  CPPUNIT_ASSERT_EQUAL(7, container().size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefg").inspect(), container().inspect());
}

void
sk::io::test::BufferedOutputStreamTest::
testWriteLargerChunk()
{
  _streamHolder.set(new BufferedOutputStream(output(), 4));
  stream().write(sk::util::Container("123412345"));
  CPPUNIT_ASSERT_EQUAL(8, container().size());
}

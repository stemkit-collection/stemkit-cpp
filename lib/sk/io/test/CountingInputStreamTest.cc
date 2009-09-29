/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "CountingInputStreamTest.h"
#include <sk/util/Container.h>
#include <sk/io/ByteArrayInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/CountingInputStream.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::CountingInputStreamTest);

sk::io::test::CountingInputStreamTest::
CountingInputStreamTest()
{
}

sk::io::test::CountingInputStreamTest::
~CountingInputStreamTest()
{
}

void
sk::io::test::CountingInputStreamTest::
setUp()
{
}

void
sk::io::test::CountingInputStreamTest::
tearDown()
{
}

void
sk::io::test::CountingInputStreamTest::
testCounting()
{
  sk::util::Container data("aaa\nbbbb\nzzzzz");
  sk::io::CountingInputStream stream(new sk::io::ByteArrayInputStream(data));
  sk::io::DataInputStream dataStream(stream);

  CPPUNIT_ASSERT_EQUAL(uint64_t(0), stream.getByteCount());
  CPPUNIT_ASSERT_EQUAL("aaa\n", dataStream.readLine());
  CPPUNIT_ASSERT_EQUAL(uint64_t(4), stream.getByteCount());
  CPPUNIT_ASSERT_EQUAL("bbbb\n", dataStream.readLine());
  CPPUNIT_ASSERT_EQUAL(uint64_t(9), stream.getByteCount());
  CPPUNIT_ASSERT_EQUAL("zzzzz", dataStream.readLine());
  CPPUNIT_ASSERT_EQUAL(uint64_t(14), stream.getByteCount());
}

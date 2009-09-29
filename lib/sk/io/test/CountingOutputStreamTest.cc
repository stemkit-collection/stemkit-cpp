/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "CountingOutputStreamTest.h"
#include <sk/util/Container.h>
#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/CountingOutputStream.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::CountingOutputStreamTest);

sk::io::test::CountingOutputStreamTest::
CountingOutputStreamTest()
{
}

sk::io::test::CountingOutputStreamTest::
~CountingOutputStreamTest()
{
}

void
sk::io::test::CountingOutputStreamTest::
setUp()
{
}

void
sk::io::test::CountingOutputStreamTest::
tearDown()
{
}

namespace {
  void writeToStream(sk::io::OutputStream& stream, const sk::util::String& data) {
    stream.write(data.getChars(), 0, data.size());
  }
}

void
sk::io::test::CountingOutputStreamTest::
testCounting()
{
  sk::util::Container container;
  sk::io::CountingOutputStream stream(new ByteArrayOutputStream(container));
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), stream.getByteCount());

  writeToStream(stream, "aaa");
  writeToStream(stream, "hello");

  CPPUNIT_ASSERT_EQUAL(uint64_t(8), stream.getByteCount());
  CPPUNIT_ASSERT_EQUAL(8, container.size());
}

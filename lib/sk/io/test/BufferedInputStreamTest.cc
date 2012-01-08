/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "BufferedInputStreamTest.h"
#include "MockInputStream.h"

#include <sk/util/Holder.cxx>
#include <sk/io/BufferedInputStream.h>
#include <sk/io/EOFException.h>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::BufferedInputStreamTest);

sk::io::test::BufferedInputStreamTest::
BufferedInputStreamTest()
{
}

sk::io::test::BufferedInputStreamTest::
~BufferedInputStreamTest()
{
}

void
sk::io::test::BufferedInputStreamTest::
setUp()
{
  _mockHolder.set(new MockInputStream());
  _streamHolder.set(new BufferedInputStream(mock()));
}

void
sk::io::test::BufferedInputStreamTest::
tearDown()
{
  _streamHolder.clear();
  _mockHolder.clear();
}

void
sk::io::test::BufferedInputStreamTest::
testBuffer()
{
  _streamHolder.set(new BufferedInputStream(mock(), 4));
  mock().setData("1234567890");
  CPPUNIT_ASSERT_EQUAL(0, mock().chunks());

  CPPUNIT_ASSERT_EQUAL(sk::util::Container("123").inspect(), sk::util::Container(stream().read(3)).inspect());

  CPPUNIT_ASSERT_EQUAL(1, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(4, mock().chunk(0).size());

  CPPUNIT_ASSERT_EQUAL('4', stream().read());
  CPPUNIT_ASSERT_EQUAL(1, mock().chunks());

  CPPUNIT_ASSERT_EQUAL('5', stream().read());
  CPPUNIT_ASSERT_EQUAL(2, mock().chunks());
  CPPUNIT_ASSERT_EQUAL(4, mock().chunk(1).size());

  CPPUNIT_ASSERT_EQUAL(sk::util::Container("678").inspect(), sk::util::Container(stream().read(10)).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::Container("90").inspect(), sk::util::Container(stream().read(10)).inspect());
  CPPUNIT_ASSERT_THROW(stream().read(), sk::io::EOFException);
}

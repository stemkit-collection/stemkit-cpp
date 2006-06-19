/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileStreamsTest.h"
#include <sk/io/FileInputStream.h>
#include <sk/io/FileOutputStream.h>
#include <sk/io/DataInputStream.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileStreamsTest);

sk::io::test::FileStreamsTest::
FileStreamsTest()
{
}

sk::io::test::FileStreamsTest::
~FileStreamsTest()
{
}

void
sk::io::test::FileStreamsTest::
setUp()
{
}

void
sk::io::test::FileStreamsTest::
tearDown()
{
}

void
sk::io::test::FileStreamsTest::
testRead()
{
  sk::io::FileInputStream stream("testdata");
  sk::io::DataInputStream data(stream);

  sk::util::String expected = "# This comment is needed for tests.\n";
  CPPUNIT_ASSERT_EQUAL(expected.inspect(), data.readLine().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("testdata"), stream.getFile().getName());
}

void
sk::io::test::FileStreamsTest::
testWriteOpen()
{
  sk::io::FileOutputStream stream("testdata", true);
  CPPUNIT_ASSERT_EQUAL(sk::util::String("testdata"), stream.getFile().getName());
}

void
sk::io::test::FileStreamsTest::
testDescriptorsSame()
{
  sk::io::FileInputStream stream("testdata");

  CPPUNIT_ASSERT_EQUAL(stream.getFileDescriptor().getFileNumber(), stream.getFile().getFileDescriptor().getFileNumber());
}

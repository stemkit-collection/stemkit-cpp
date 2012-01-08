/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileTest.h"
#include <sk/io/File.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/IOException.h>

#include <sk/cppunit/SourcePath.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileTest);

sk::io::test::FileTest::
FileTest()
{
}

sk::io::test::FileTest::
~FileTest()
{
}

void
sk::io::test::FileTest::
setUp()
{
}

void
sk::io::test::FileTest::
tearDown()
{
}

void
sk::io::test::FileTest::
testOpenRead()
{
  sk::io::File file(sk::cppunit::SourcePath::make("testdata"));
  sk::io::FileDescriptor descriptor = file.getFileDescriptor();

  char c;
  CPPUNIT_ASSERT_EQUAL(1, descriptor.read(&c, 0, 1));
  CPPUNIT_ASSERT_EQUAL('#', c);
}

void
sk::io::test::FileTest::
testOpenUnexistent()
{
  CPPUNIT_ASSERT_THROW(sk::io::File("NO_SUCH_FILE"), sk::io::IOException);
}

void
sk::io::test::FileTest::
testOpenWrite()
{
  CPPUNIT_ASSERT_NO_THROW(sk::io::File("testdata", "a"));
}

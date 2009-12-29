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
#include <sk/io/FileStreamCoupler.cxx>

#include <sk/cppunit/SourcePath.h>

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
  const sk::util::String datafile = sk::cppunit::SourcePath::make("testdata");
  sk::io::FileInputStream stream(datafile);
  sk::io::DataInputStream data(stream);

  CPPUNIT_ASSERT_EQUAL("# This comment is needed for tests.", data.readLine().trim());
  CPPUNIT_ASSERT_EQUAL(sk::util::String(datafile), stream.getFile().getName());
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

void
sk::io::test::FileStreamsTest::
testAvailable()
{
  sk::io::FileInputStream stream(sk::cppunit::SourcePath::make("testdata"));

  int available = stream.available();

  CPPUNIT_ASSERT(available == 81 || available==85);
  CPPUNIT_ASSERT_EQUAL(20, stream.skip(20));
  CPPUNIT_ASSERT_EQUAL(available-20, int(stream.available()));
}

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/io/FileInfo.h>

#include "DirTest.h"
#include <sk/io/Dir.h>
#include <sk/util/Pathname.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/processor/Copying.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::DirTest);

sk::io::test::DirTest::
DirTest()
{
}

sk::io::test::DirTest::
~DirTest()
{
}

void
sk::io::test::DirTest::
setUp()
{
}

void
sk::io::test::DirTest::
tearDown()
{
}

void
sk::io::test::DirTest::
testEachEntry()
{
  sk::io::Dir current(".");
  CPPUNIT_ASSERT_EQUAL(".", current.getPath().toString());

  sk::util::ArrayList<sk::util::Pathname> entries;
  current.forEachEntry(sk::util::processor::Copying<sk::util::Pathname>(entries));

  CPPUNIT_ASSERT(entries.size() > 0);
}

void
sk::io::test::DirTest::
testEachRegularFile()
{
  sk::io::Dir current(".");
  CPPUNIT_ASSERT_EQUAL(".", current.getPath().toString());

  sk::util::ArrayList<sk::io::FileInfo> entries;
  current.forEachRegularFile(sk::util::processor::Copying<const sk::io::FileInfo, sk::io::FileInfo>(entries));

  CPPUNIT_ASSERT(entries.size() > 0);
}

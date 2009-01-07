/* vim: set sw=2: 
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PointingCyclerTest.h"
#include <logger/FileDestination.h>
#include <logger/PointingCycler.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/File.h>

#include <sk/cppunit/StringAssert.h>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::logger::test::PointingCyclerTest);

using sk::util::File;

sk::rt::logger::test::PointingCyclerTest::
PointingCyclerTest()
{
}

sk::rt::logger::test::PointingCyclerTest::
~PointingCyclerTest()
{
}

void
sk::rt::logger::test::PointingCyclerTest::
setUp()
{
  unlink("abc");
  unlink("abc-1");
  unlink("abc-2");
  unlink("abc-3");

  _fileHolder.set(new logger::FileDestination(logger::PointingCycler(sk::util::Pathname("abc"))));
}

void
sk::rt::logger::test::PointingCyclerTest::
tearDown()
{
  unlink("abc");
  unlink("abc-1");
  unlink("abc-2");
  unlink("abc-3");

  _fileHolder.clear();
}

void
sk::rt::logger::test::PointingCyclerTest::
testDefaults()
{
  CPPUNIT_ASSERT_EQUAL(2048, _fileHolder.get().getCycler().getSize());
  CPPUNIT_ASSERT_EQUAL(3, _fileHolder.get().getCycler().getChunks());
}

void
sk::rt::logger::test::PointingCyclerTest::
testEarlyMakeReady()
{
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-1"));

  _fileHolder.get().makeReady();
  _fileHolder.get().close();

  File master("abc");
  File data("abc-1");

  CPPUNIT_ASSERT_EQUAL("[abc 1 of 3]", master.getLine());
  CPPUNIT_ASSERT_THROW(master.getLine(), sk::util::IllegalStateException);
  
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 3]", data.getLine());
  CPPUNIT_ASSERT_THROW(data.getLine(), sk::util::IllegalStateException);
}

void
sk::rt::logger::test::PointingCyclerTest::
testDelayedDispatch()
{
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-1"));

  _fileHolder.get().dispatch("hello, world!!!\n", 16);
  _fileHolder.get().close();

  File master("abc");
  File data("abc-1");
  
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 3]", master.getLine());
  CPPUNIT_ASSERT_THROW(master.getLine(), sk::util::IllegalStateException);

  CPPUNIT_ASSERT_EQUAL("[abc 1 of 3]", data.getLine());
  CPPUNIT_ASSERT_EQUAL("hello, world!!!", data.getLine());
  CPPUNIT_ASSERT_THROW(data.getLine(), sk::util::IllegalStateException);
}

void
sk::rt::logger::test::PointingCyclerTest::
testCycling()
{
  _fileHolder.get().getCycler().setChunks(2);
  _fileHolder.get().getCycler().setSize(20);

  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-1"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-2"));

  _fileHolder.get().dispatch("aaaa\n", 5);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]", File("abc").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]\naaaa", File("abc-1").getLines());
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-2"));

  _fileHolder.get().dispatch("bbbb\n", 5);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]", File("abc").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]\naaaa\nbbbb\n[---Switched---]", File("abc-1").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]", File("abc-2").getLines());

  _fileHolder.get().dispatch("cccc\n", 5);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]", File("abc").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]\naaaa\nbbbb\n[---Switched---]", File("abc-1").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]\ncccc", File("abc-2").getLines());

  _fileHolder.get().dispatch("dddd\n", 5);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]", File("abc").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]", File("abc-1").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]\ncccc\ndddd\n[---Switched---]", File("abc-2").getLines());

  _fileHolder.get().dispatch("eeee\n", 5);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]", File("abc").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 1 of 2]\neeee", File("abc-1").getLines());
  CPPUNIT_ASSERT_EQUAL("[abc 2 of 2]\ncccc\ndddd\n[---Switched---]", File("abc-2").getLines());
}

void
sk::rt::logger::test::PointingCyclerTest::
testEnsureChunks()
{
  _fileHolder.get().getCycler().setChunks(2);

  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-1"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-2"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-3"));

  _fileHolder.get().getCycler().ensureChunks();

  CPPUNIT_ASSERT_EQUAL(true, File::exists("abc"));
  CPPUNIT_ASSERT_EQUAL(true, File::exists("abc-1"));
  CPPUNIT_ASSERT_EQUAL(true, File::exists("abc-2"));
  CPPUNIT_ASSERT_EQUAL(false, File::exists("abc-3"));
}

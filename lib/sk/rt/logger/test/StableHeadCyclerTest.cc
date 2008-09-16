/* vim: set sw=2: 
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StableHeadCyclerTest.h"
#include <logger/FileDestination.h>
#include <logger/StableHeadCycler.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.cxx>
#include <fstream>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::logger::test::StableHeadCyclerTest);

sk::rt::logger::test::StableHeadCyclerTest::
StableHeadCyclerTest()
{
}

sk::rt::logger::test::StableHeadCyclerTest::
~StableHeadCyclerTest()
{
}

void
sk::rt::logger::test::StableHeadCyclerTest::
setUp()
{
  unlink("abc");
  unlink("abc-1");
  unlink("abc-2");
  unlink("abc-3");

  _fileHolder.set(new logger::FileDestination(logger::StableHeadCycler(sk::util::Pathname("abc"))));
}

void
sk::rt::logger::test::StableHeadCyclerTest::
tearDown()
{
  unlink("abc");
  unlink("abc-1");
  unlink("abc-2");
  unlink("abc-3");

  _fileHolder.clear();
}

void
sk::rt::logger::test::StableHeadCyclerTest::
testDefaults()
{
  CPPUNIT_ASSERT_EQUAL(2048, _fileHolder.get().getCycler().getSize());
  CPPUNIT_ASSERT_EQUAL(3, _fileHolder.get().getCycler().getChunks());
}

void
sk::rt::logger::test::StableHeadCyclerTest::
testEarlyMakeReady()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  _fileHolder.get().makeReady();
  _fileHolder.get().close();

  std::ifstream stream("abc");
  std::string depot;

  CPPUNIT_ASSERT_EQUAL(true, stream.good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 0 of 3]"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
}

void
sk::rt::logger::test::StableHeadCyclerTest::
testDelayedDispatch()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  _fileHolder.get().dispatch("hello, world!!!\n", 16);
  _fileHolder.get().close();

  std::ifstream stream("abc");
  std::string depot;
  
  CPPUNIT_ASSERT_EQUAL(true, stream.good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("hello, world!!!"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
}

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
#include <fstream>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::logger::test::PointingCyclerTest);

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
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc-1").good());

  _fileHolder.get().makeReady();
  _fileHolder.get().close();

  std::ifstream master("abc");
  std::ifstream data("abc-1");
  std::string depot;

  CPPUNIT_ASSERT_EQUAL(true, master.good());
  CPPUNIT_ASSERT_EQUAL(true, data.good());

  CPPUNIT_ASSERT_EQUAL(true, std::getline(master, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 1 of 3]"), depot);
  CPPUNIT_ASSERT_EQUAL(true, std::getline(data, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 1 of 3]"), depot);

  CPPUNIT_ASSERT_EQUAL(false, std::getline(master, depot).good());
  CPPUNIT_ASSERT_EQUAL(false, std::getline(data, depot).good());
}

void
sk::rt::logger::test::PointingCyclerTest::
testDelayedDispatch()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc-1").good());

  _fileHolder.get().dispatch("hello, world!!!\n", 16);
  _fileHolder.get().close();

  std::ifstream master("abc");
  std::ifstream data("abc-1");
  std::string depot;
  
  CPPUNIT_ASSERT_EQUAL(true, master.good());
  CPPUNIT_ASSERT_EQUAL(true, data.good());

  CPPUNIT_ASSERT_EQUAL(true, std::getline(master, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 1 of 3]"), depot);
  CPPUNIT_ASSERT_EQUAL(true, std::getline(data, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 1 of 3]"), depot);

  CPPUNIT_ASSERT_EQUAL(false, std::getline(master, depot).good());

  CPPUNIT_ASSERT_EQUAL(true, std::getline(data, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("hello, world!!!"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(data, depot).good());
}

void
sk::rt::logger::test::PointingCyclerTest::
testCycling()
{
  _fileHolder.get().getCycler().setChunks(2);
  _fileHolder.get().getCycler().setSize(30);

  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc-1").good());
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc-2").good());

  _fileHolder.get().dispatch("hello, world!!!\n", 16);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc-1").good());
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc-2").good());

  _fileHolder.get().dispatch("hello, world!!!\n", 16);
  _fileHolder.get().close();

  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc-1").good());
  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc-2").good());
}

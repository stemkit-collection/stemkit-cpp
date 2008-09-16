/* vim: set sw=2: 
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PointingCyclerTest.h"
#include <logger/PipeDestination.h>
#include <logger/FileDestination.h>
#include <logger/PointingCycler.h>
#include <sk/util/Pathname.h>
#include <sk/util/Integer.h>
#include <sk/util/SystemExit.h>
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

  _fileHolder.set(new logger::FileDestination(logger::PointingCycler(sk::util::Pathname("abc"))));
  _pipeHolder.set(new logger::PipeDestination(_fileHolder.get()));
}

void
sk::rt::logger::test::PointingCyclerTest::
tearDown()
{
  unlink("abc");
  _fileHolder.clear();
  _pipeHolder.clear();
}

void
sk::rt::logger::test::PointingCyclerTest::
testDefaults()
{
  CPPUNIT_ASSERT_EQUAL(2048, _fileHolder.get().getSize());
  CPPUNIT_ASSERT_EQUAL(3, _fileHolder.get().getBackups());
}

void
sk::rt::logger::test::PointingCyclerTest::
testEarlyMakeReady()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  _pipeHolder.get().makeReady();
  sleep(1);

  std::ifstream stream("abc");
  std::string depot;

  CPPUNIT_ASSERT_EQUAL(true, stream.good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("[abc 0 of 3]"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
}

void
sk::rt::logger::test::PointingCyclerTest::
testDelayedDispatch()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  _pipeHolder.get().dispatch("hello, world!!!\n", 16);
  sleep(1);

  std::ifstream stream("abc");
  std::string depot;
  
  CPPUNIT_ASSERT_EQUAL(true, stream.good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(std::string("hello, world!!!"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
}

void
sk::rt::logger::test::PointingCyclerTest::
testMessageOnExit()
{
  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  _pipeHolder.get().makeReady();
  sleep(1);

  std::ifstream stream("abc");
  sk::util::String depot;

  CPPUNIT_ASSERT_EQUAL(true, stream.good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("[abc 0 of 3]"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
  
  stream.clear();
  _pipeHolder.get().dispatch("hello, world!!!\n", 16);
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("hello, world!!!"), depot);
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());

  stream.clear();
  _pipeHolder.get().close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(true, depot.startsWith("### "));
  CPPUNIT_ASSERT_EQUAL(true, depot.endsWith("NOTICE:PIPE: Exit"));
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
}

void
sk::rt::logger::test::PointingCyclerTest::
testWriteErrorAfterClose()
{
  _pipeHolder.get().makeReady();
  _pipeHolder.get().close();

  for(int counter=3; counter ;--counter) {
    try {
      _pipeHolder.get().dispatch("abc", 3);
      CPPUNIT_FAIL("No expected exception, iteration=" + sk::util::Integer::toString(counter));
    }
    catch(const sk::util::SystemExit& exception) {}
  }
}

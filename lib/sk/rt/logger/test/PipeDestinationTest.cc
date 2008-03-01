/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipeDestinationTest.h"
#include <logger/PipeDestination.h>
#include <logger/FileDestination.h>
#include <sk/util/Pathname.h>
#include <fstream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::logger::test::PipeDestinationTest);

sk::rt::logger::test::PipeDestinationTest::
PipeDestinationTest()
{
}

sk::rt::logger::test::PipeDestinationTest::
~PipeDestinationTest()
{
}

void
sk::rt::logger::test::PipeDestinationTest::
setUp()
{
}

void
sk::rt::logger::test::PipeDestinationTest::
tearDown()
{
}

void
sk::rt::logger::test::PipeDestinationTest::
testBasics()
{
  unlink("abc");
  logger::FileDestination file(sk::util::Pathname("abc"));
  logger::PipeDestination destination(file);

  CPPUNIT_ASSERT_EQUAL(false, std::ifstream("abc").good());
  destination.makeReady();

  std::ifstream stream("abc");
  std::string depot;

  CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc").good());
  CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
  CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());

  destination.dispatch("hello, world!!!\n", 16);
  {
    std::ifstream stream("abc");
    std::string depot;
    
    CPPUNIT_ASSERT_EQUAL(true, std::ifstream("abc").good());
    CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
    CPPUNIT_ASSERT_EQUAL(true, std::getline(stream, depot).good());
    CPPUNIT_ASSERT_EQUAL(std::string("hello, world!!!"), depot);
    CPPUNIT_ASSERT_EQUAL(false, std::getline(stream, depot).good());
  }
}

/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "LoggerTest.h"
#include <sk/rt/Logger.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::LoggerTest);

sk::rt::tests::LoggerTest::
LoggerTest()
{
}

sk::rt::tests::LoggerTest::
~LoggerTest()
{
}

void
sk::rt::tests::LoggerTest::
setUp()
{
}

void
sk::rt::tests::LoggerTest::
tearDown()
{
}

void
sk::rt::tests::LoggerTest::
testCreateName()
{
  Logger logger("abc");
}

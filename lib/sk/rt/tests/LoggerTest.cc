/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "LoggerTest.h"
#include <sk/rt/Logger.h>
#include <sk/rt/logger/Level.h>

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
  _stream.clear();
  Logger::controller().setStream(_stream);
}

void
sk::rt::tests::LoggerTest::
tearDown()
{
  _stream.clear();
}

void
sk::rt::tests::LoggerTest::
testDefaultNoOutputButError()
{
  Logger logger("abc");

  logger.info() << "aaa";
  logger.warning() << "bbb";
  logger.notice() << "ccc";
  logger.debug() << "ddd";
  logger.detail() << "eee";

  CPPUNIT_ASSERT_EQUAL(true, _stream.str().empty());

  logger.error() << "zzz";
  CPPUNIT_ASSERT_EQUAL(sk::util::String("ERROR:abc: zzz\n").inspect(), sk::util::String(_stream.str()).inspect());
}

void
sk::rt::tests::LoggerTest::
testConcatenation()
{
  Logger logger("zzz");

  // Logger::controller().setShowPid(true);
  // Logger::controller().setShowTime(true);
  // Logger::controller().setShowObject(true);

  logger.error() << "aaa" << ' ' << "bbb" << ' ' << "ccc";
  logger.error() << "ddd";

  CPPUNIT_ASSERT_EQUAL(sk::util::String("ERROR:zzz: aaa bbb ccc\nERROR:zzz: ddd\n").inspect(), sk::util::String(_stream.str()).inspect());
}

void
sk::rt::tests::LoggerTest::
testScope()
{
  Logger::controller().setLevel(logger::Level::INFO);
  {
    const Logger logger("s1");
    logger.info() << "a";

    {
      Logger inner = logger.scope("s2");
      inner.info() << "b";
    }
    logger.info() << "c";
  }
  CPPUNIT_ASSERT_EQUAL(
    sk::util::String("INFO:s1: Enter\nINFO:s1: a\nINFO:s1#s2: Enter\nINFO:s1#s2: b\nINFO:s1#s2: Leave\nINFO:s1: c\nINFO:s1: Leave\n").inspect(),
    sk::util::String(_stream.str()).inspect()
  );
}
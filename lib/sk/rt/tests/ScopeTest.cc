/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ScopeTest.h"
#include <sk/rt/Scope.h>
#include <sk/rt/logger/Level.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::ScopeTest);

sk::rt::tests::ScopeTest::
ScopeTest()
{
}

sk::rt::tests::ScopeTest::
~ScopeTest()
{
}

void
sk::rt::tests::ScopeTest::
setUp()
{
  _stream.clear();
  Scope::controller().getConfig().setLogStream(_stream);
}

void
sk::rt::tests::ScopeTest::
tearDown()
{
  _stream.clear();
}

void
sk::rt::tests::ScopeTest::
testDefaultNoOutputButError()
{
  Scope scope("abc");

  scope.info() << "aaa";
  scope.warning() << "bbb";
  scope.notice() << "ccc";
  scope.debug() << "ddd";
  scope.detail() << "eee";

  CPPUNIT_ASSERT_EQUAL(true, _stream.str().empty());

  scope.error() << "zzz";
  CPPUNIT_ASSERT_EQUAL(sk::util::String("ERROR:abc: zzz\n").inspect(), sk::util::String(_stream.str()).inspect());
}

void
sk::rt::tests::ScopeTest::
testConcatenation()
{
  Scope scope("zzz");

  // Logger::controller().setShowPid(true);
  // Logger::controller().setShowTime(true);
  // Logger::controller().setShowObject(true);

  scope.error() << "aaa" << ' ' << "bbb" << ' ' << "ccc";
  scope.error() << "ddd";

  CPPUNIT_ASSERT_EQUAL(sk::util::String("ERROR:zzz: aaa bbb ccc\nERROR:zzz: ddd\n").inspect(), sk::util::String(_stream.str()).inspect());
}

void
sk::rt::tests::ScopeTest::
testScope()
{
  Scope::controller().getConfig().setLogLevel(logger::Level::INFO);
  {
    const Scope scope("s1");
    scope.info() << "a";

    {
      Scope inner = scope.scope("s2");
      inner.info() << "b";
    }
    scope.info() << "c";
  }
  CPPUNIT_ASSERT_EQUAL(
    sk::util::String("INFO:s1: Enter (name)\nINFO:s1: a\nINFO:s1#s2: Enter (scope)\nINFO:s1#s2: b\nINFO:s1#s2: Leave\nINFO:s1: c\nINFO:s1: Leave\n").inspect(),
    sk::util::String(_stream.str()).inspect()
  );
}

void
sk::rt::tests::ScopeTest::
testDefaultProperties()
{
  Scope scope("s1");
  CPPUNIT_ASSERT_EQUAL(false, scope.hasProperty("abc"));
  CPPUNIT_ASSERT_EQUAL(45, scope.getProperty("abc", 45));
  CPPUNIT_ASSERT_EQUAL(true, scope.getProperty("abc", sk::util::Boolean::TRUE));
  CPPUNIT_ASSERT_EQUAL(false, scope.getProperty("abc", sk::util::Boolean::FALSE));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("zzz"), scope.getProperty("abc", "zzz"));
}

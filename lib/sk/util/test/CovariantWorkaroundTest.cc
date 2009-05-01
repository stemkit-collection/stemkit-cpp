/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "CovariantWorkaroundTest.h"
#include <sk/util/Holder.cxx>
#include <sk/util/covariant.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::CovariantWorkaroundTest);

sk::util::test::CovariantWorkaroundTest::
CovariantWorkaroundTest()
{
}

sk::util::test::CovariantWorkaroundTest::
~CovariantWorkaroundTest()
{
}

void
sk::util::test::CovariantWorkaroundTest::
setUp()
{
}

void
sk::util::test::CovariantWorkaroundTest::
tearDown()
{
}

namespace {
  struct Probe : public virtual sk::util::Object {
    Probe(int& counter) : _counter(counter) {
      ++_counter;
    }
    ~Probe() {
      --_counter;
    }
    int& _counter;
  };
}

void
sk::util::test::CovariantWorkaroundTest::
testProbe()
{
  int counter = 0;
  {
    Probe p1(counter);
    CPPUNIT_ASSERT_EQUAL(1, counter);

    Probe p2(counter);
    CPPUNIT_ASSERT_EQUAL(2, counter);

    Probe p3(counter);
    CPPUNIT_ASSERT_EQUAL(3, counter);
  }
  CPPUNIT_ASSERT_EQUAL(0, counter);

  sk::util::Holder<sk::util::Object> holder(new Probe(counter));
  CPPUNIT_ASSERT_EQUAL(1, counter);
  holder.clear();
  CPPUNIT_ASSERT_EQUAL(0, counter);
}

void
sk::util::test::CovariantWorkaroundTest::
testCastSucceeds()
{
  int counter = 0;
  sk::util::Holder<sk::util::Object> holder(new Probe(counter));
  CPPUNIT_ASSERT_EQUAL(1, counter);

  Probe* p = sk::util::covariant<Probe>(&holder.get());
  CPPUNIT_ASSERT_EQUAL(1, counter);
}

void
sk::util::test::CovariantWorkaroundTest::
testFailedCastDeletesProbe()
{
  int counter = 0;
  Probe* probe = new Probe(counter);
  CPPUNIT_ASSERT_EQUAL(1, counter);

  CPPUNIT_ASSERT_THROW(sk::util::covariant<sk::util::String>(probe), sk::util::ClassCastException);
  CPPUNIT_ASSERT_EQUAL(0, counter);
}

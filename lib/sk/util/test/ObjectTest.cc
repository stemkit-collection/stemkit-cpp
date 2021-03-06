/*  vi: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ObjectTest.h"
#include <sk/util/Object.h>
#include <sk/util/Class.h>
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ObjectTest);

sk::util::test::ObjectTest::
ObjectTest()
{
}

sk::util::test::ObjectTest::
~ObjectTest()
{
}

struct sk::util::test::ObjectTest::SampleObject : public virtual sk::util::Object {
};

void
sk::util::test::ObjectTest::
setUp()
{
  _object.reset(new SampleObject());
}

void
sk::util::test::ObjectTest::
tearDown()
{
}

const sk::util::Object&
sk::util::test::ObjectTest::
getObject() const
{
  return *_object;
}

void
sk::util::test::ObjectTest::
testClassName()
{
  CPPUNIT_ASSERT_EQUAL(String("sk::util::Object"), getObject().getClass().getName());
}

void
sk::util::test::ObjectTest::
testId()
{
  CPPUNIT_ASSERT(SampleObject().getId() != getObject().getId());
  CPPUNIT_ASSERT(SampleObject().getId() != SampleObject().getId());
}

namespace {
  struct Object : public virtual sk::util::Object {
    virtual uint64_t getId() const {
      return 21;
    }
  } object;
}

void
sk::util::test::ObjectTest::
testToString()
{
  CPPUNIT_ASSERT_EQUAL(String("<sk::util::Object#15>"), object.toString());
}

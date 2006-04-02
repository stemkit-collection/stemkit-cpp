/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ObjectTest.h"
#include <sk/util/Object.h>
#include <sk/util/Class.h>
#include <sk/util/String.h>

sk::util::test::ObjectTest::
ObjectTest()
{
}

sk::util::test::ObjectTest::
~ObjectTest()
{
}

void
sk::util::test::ObjectTest::
setUp()
{
  class Object : public virtual sk::util::Object {
  };
  _object.reset(new Object());
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
  CPPUNIT_ASSERT_EQUAL(reinterpret_cast<unsigned int>(&getObject()), getObject().getId());
}

namespace {
  struct Object : public virtual sk::util::Object {
    virtual unsigned int getId() const {
      return 21;
    }
  } object;
}

void
sk::util::test::ObjectTest::
testToString()
{
  CPPUNIT_ASSERT_EQUAL(String("sk::util::Object#21"), object.toString());
}

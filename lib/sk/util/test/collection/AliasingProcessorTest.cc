/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "AliasingProcessorTest.h"
#include <sk/util/ArrayList.cxx>
#include <sk/util/processor/Aliasing.hxx>
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::AliasingProcessorTest);

sk::util::test::AliasingProcessorTest::
AliasingProcessorTest()
{
}

sk::util::test::AliasingProcessorTest::
~AliasingProcessorTest()
{
}

void
sk::util::test::AliasingProcessorTest::
setUp()
{
}

void
sk::util::test::AliasingProcessorTest::
tearDown()
{
}

void
sk::util::test::AliasingProcessorTest::
testAliasing()
{
  sk::util::ArrayList<sk::util::String>::Copying source;
  sk::util::ArrayList<sk::util::String> target;

  source.add("aaa");
  source.add("bbb");
  source.add("ccc");

  source.forEach(processor::Aliasing<sk::util::String>(target));

  CPPUNIT_ASSERT_EQUAL(3, target.size());
  CPPUNIT_ASSERT(&source.get(0) == &target.get(0));
  CPPUNIT_ASSERT(&source.get(1) == &target.get(1));
  CPPUNIT_ASSERT(&source.get(2) == &target.get(2));
}

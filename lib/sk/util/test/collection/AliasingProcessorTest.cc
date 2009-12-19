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
#include <sk/util/AliasingProcessor.cxx>
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
  sk::util::ArrayList<sk::util::String> source;
  sk::util::ArrayList<sk::util::String> target;

  source.add(new sk::util::String("aaa"));
  source.add(new sk::util::String("bbb"));
  source.add(new sk::util::String("ccc"));

  source.forEach(AliasingProcessor<sk::util::String>(target));

  CPPUNIT_ASSERT_EQUAL(3, target.size());
  CPPUNIT_ASSERT(&source.get(0) == &target.get(0));
  CPPUNIT_ASSERT(&source.get(1) == &target.get(1));
  CPPUNIT_ASSERT(&source.get(2) == &target.get(2));
}

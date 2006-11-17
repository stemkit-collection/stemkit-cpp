/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "TrashDisposerTest.h"
#include <sk/runtime/TrashDisposer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::runtime::test::TrashDisposerTest);

sk::runtime::test::TrashDisposerTest::
TrashDisposerTest()
{
}

sk::runtime::test::TrashDisposerTest::
~TrashDisposerTest()
{
}

void
sk::runtime::test::TrashDisposerTest::
setUp()
{
}

void
sk::runtime::test::TrashDisposerTest::
tearDown()
{
}

void
sk::runtime::test::TrashDisposerTest::
testCreate()
{
  TrashDisposer disposer;
}

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ConfiguratorTest.h"
#include <sk/runtime/Configurator.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::runtime::test::ConfiguratorTest);

sk::runtime::test::ConfiguratorTest::
ConfiguratorTest()
{
}

sk::runtime::test::ConfiguratorTest::
~ConfiguratorTest()
{
}

void
sk::runtime::test::ConfiguratorTest::
setUp()
{
}

void
sk::runtime::test::ConfiguratorTest::
tearDown()
{
}

void
sk::runtime::test::ConfiguratorTest::
testCreate()
{
  Configurator configurator;
}

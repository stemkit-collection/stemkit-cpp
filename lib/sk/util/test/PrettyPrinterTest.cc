/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "PrettyPrinterTest.h"
#include <sstream>
#include <sk/util/PrettyPrinter.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PrettyPrinterTest);

sk::util::test::PrettyPrinterTest::
PrettyPrinterTest()
{
}

sk::util::test::PrettyPrinterTest::
~PrettyPrinterTest()
{
}

void
sk::util::test::PrettyPrinterTest::
setUp()
{
}

void
sk::util::test::PrettyPrinterTest::
tearDown()
{
}

void
sk::util::test::PrettyPrinterTest::
testBasics()
{
  std::ostringstream stream;
  sk::util::PrettyPrinter printer(stream);

  printer.print("<Abc: nnn=[2: 0*(), 1&() ], ttt=ABC>");
  CPPUNIT_ASSERT_EQUAL("<StructNode:Abc: nnn=<CollectionNode:2: 0*<HolderNode: empty>, 1&<HolderNode: empty>>, ttt=<TextNode: \"ABC\">>", stream.str());
}
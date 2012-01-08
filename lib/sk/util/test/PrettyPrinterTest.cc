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

  printer.print("<Abc: nnn=[2: 0*(), 1&(), 2*<Zzz: n1=AAA, n2=BBB> ], ttt=ABC>");
  CPPUNIT_ASSERT_EQUAL("<Abc: \n  nnn => [2: \n    0*()\n    1&()\n    2*<Zzz: n1 => AAA n2 => BBB >\n  ]\n  ttt => ABC\n>\n", stream.str());
}

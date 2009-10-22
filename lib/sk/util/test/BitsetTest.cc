/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "BitsetTest.h"
#include <sk/util/Bitset.h>
#include <limits>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::BitsetTest);

sk::util::test::BitsetTest::
BitsetTest()
{
}

sk::util::test::BitsetTest::
~BitsetTest()
{
}

void
sk::util::test::BitsetTest::
setUp()
{
}

void
sk::util::test::BitsetTest::
tearDown()
{
}

void
sk::util::test::BitsetTest::
testEmpty()
{
  sk::util::Bitset bitset;

  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMin());
  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMax());

  CPPUNIT_ASSERT(bitset.isOn(0) == false);
  CPPUNIT_ASSERT(bitset.isOn(100) == false);
  CPPUNIT_ASSERT(bitset.isOn(uint32_t(-1)) == false);

  CPPUNIT_ASSERT(bitset.isOff(0) == true);
  CPPUNIT_ASSERT(bitset.isOff(100) == true);
  CPPUNIT_ASSERT(bitset.isOff(std::numeric_limits<uint32_t>::max()) == true);

  CPPUNIT_ASSERT_EQUAL("0<>0", bitset.inspect());
}

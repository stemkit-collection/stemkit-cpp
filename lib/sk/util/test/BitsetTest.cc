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

  CPPUNIT_ASSERT_EQUAL(0, bitset.capacity());

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

void
sk::util::test::BitsetTest::
testUpperBounds()
{
  sk::util::Bitset bitset(7);

  CPPUNIT_ASSERT_EQUAL(1, bitset.capacity());
  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMin());
  CPPUNIT_ASSERT_EQUAL(uint32_t(32), bitset.getMax());

  CPPUNIT_ASSERT(bitset.isOn(0) == false);
  CPPUNIT_ASSERT(bitset.isOn(100) == false);
  CPPUNIT_ASSERT(bitset.isOn(uint32_t(-1)) == false);

  CPPUNIT_ASSERT(bitset.isOff(0) == true);
  CPPUNIT_ASSERT(bitset.isOff(100) == true);
  CPPUNIT_ASSERT(bitset.isOff(std::numeric_limits<uint32_t>::max()) == true);

  CPPUNIT_ASSERT(bitset.set(21) == false);
  CPPUNIT_ASSERT(bitset.set(21) == true);

  CPPUNIT_ASSERT(bitset.set(22) == false);
  CPPUNIT_ASSERT(bitset.set(24) == false);
  CPPUNIT_ASSERT(bitset.set(25) == false);

  CPPUNIT_ASSERT(bitset.isOn(21) == true);
  CPPUNIT_ASSERT(bitset.isOn(22) == true);
  CPPUNIT_ASSERT(bitset.isOn(23) == false);
  CPPUNIT_ASSERT(bitset.isOn(24) == true);
  CPPUNIT_ASSERT(bitset.isOn(25) == true);

  CPPUNIT_ASSERT(bitset.clear(24) == true);
  CPPUNIT_ASSERT(bitset.clear(25) == true);
  CPPUNIT_ASSERT(bitset.clear(24) == false);
  CPPUNIT_ASSERT(bitset.clear(25) == false);

  CPPUNIT_ASSERT(bitset.isOn(24) == false);
  CPPUNIT_ASSERT(bitset.isOn(25) == false);

  CPPUNIT_ASSERT_EQUAL("0<00000000000000000000011000000000>32", bitset.inspect());
  CPPUNIT_ASSERT_EQUAL(1, bitset.capacity());
}

void 
sk::util::test::BitsetTest::
testImplicitCapacityAdjustment()
{
  Bitset bitset;

  CPPUNIT_ASSERT_EQUAL(0, bitset.capacity());
  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMin());
  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMax());

  bitset.set(1022);

  CPPUNIT_ASSERT_EQUAL(uint32_t(0), bitset.getMin());
  CPPUNIT_ASSERT_EQUAL(uint32_t(1024), bitset.getMax());
  CPPUNIT_ASSERT_EQUAL(32, bitset.capacity());

  bitset.setLowerBound(1000);
  CPPUNIT_ASSERT_EQUAL(uint32_t(992), bitset.getMin());
  CPPUNIT_ASSERT_EQUAL(uint32_t(1024), bitset.getMax());

  CPPUNIT_ASSERT_EQUAL(1, bitset.capacity());
  CPPUNIT_ASSERT(bitset.isOn(1022) == true);
  CPPUNIT_ASSERT_EQUAL("992<00000000000000000000000000000010>1024", bitset.inspect());
}

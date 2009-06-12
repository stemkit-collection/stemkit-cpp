/*  vim:sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ArrayListTest.h"
#include <sk/util/ArrayList.cxx>
#include <sk/util/Holder.cxx>
#include "Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ArrayListTest);

sk::util::test::ArrayListTest::
ArrayListTest()
{
}

sk::util::test::ArrayListTest::
~ArrayListTest()
{
}

void
sk::util::test::ArrayListTest::
setUp()
{
  Probe::resetCounter();
}

void
sk::util::test::ArrayListTest::
tearDown()
{
  Probe::resetCounter();
}

void
sk::util::test::ArrayListTest::
testCreate()
{
  ArrayList<Probe> list;

  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_EQUAL(true, list.isEmpty());
}

void
sk::util::test::ArrayListTest::
testAdd()
{
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  ArrayList<Probe> list;
  Probe p1("aaa");
  Probe p2("bbb");
  
  list.add(p1);
  list.add(p2);
  list.add(new Probe("ccc"));

  CPPUNIT_ASSERT_EQUAL(false, list.isEmpty());
  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL(3, Probe::getCounter());

  list.clear();

  CPPUNIT_ASSERT_EQUAL(true, list.isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_EQUAL(2, Probe::getCounter());
}

void
sk::util::test::ArrayListTest::
testGet()
{
  ArrayList<String> list;

  list.add(new String("aaa"));
  list.add(new String("bbb"));
  list.add(new String("ccc"));

  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(2));
  CPPUNIT_ASSERT_THROW(list.get(3), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::ArrayListTest::
testForEach()
{
  ArrayList<String> list;
  std::vector<String> target;

  CPPUNIT_ASSERT_EQUAL(size_t(0), target.size());
  list.add(new String("aaa"));
  list.add(new String("zzz"));
  list.add(new String("uuu"));

  struct Copier : public virtual sk::util::Processor<String> {
    Copier(std::vector<String>& target) 
      : _target(target) {}

    void process(String& item) const {
      _target.push_back(item);
    }
    std::vector<String>& _target;
  };

  list.forEach(Copier(target));
  CPPUNIT_ASSERT_EQUAL(size_t(3), target.size());
}

namespace {
  struct ExactStringSelector : public virtual sk::util::Selector<sk::util::String> {
    ExactStringSelector(const sk::util::String& item)
      : _item(item) {}

    bool assess(const sk::util::String& item) const {
      return _item.equals(item);
    }
    const sk::util::String& _item;
  };
};

void
sk::util::test::ArrayListTest::
testFind()
{
  ArrayList<String> list;

  list.add(new String("aaa"));
  list.add(new String("bbb"));
  list.add(new String("ccc"));
  Holder<String> holder;

  CPPUNIT_ASSERT(list.find(holder, ExactStringSelector("zzz")) == false);
  CPPUNIT_ASSERT(list.find(holder, ExactStringSelector("aaa")) == true);
  CPPUNIT_ASSERT(&holder.get() == &list.get(0));

  CPPUNIT_ASSERT(list.find(holder, ExactStringSelector("ccc")) == true);
  CPPUNIT_ASSERT(&holder.get() == &list.get(2));

  CPPUNIT_ASSERT(list.find(holder, ExactStringSelector("zzz")) == false);
  CPPUNIT_ASSERT(holder.isEmpty() == true);
}

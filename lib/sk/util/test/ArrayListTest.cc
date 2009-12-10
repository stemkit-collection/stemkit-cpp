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
#include <sk/util/OrderingChecker.h>
#include <sk/util/CopyingProcessor.cxx>
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

void 
sk::util::test::ArrayListTest::
testContains()
{
  sk::util::String s("abc");
  sk::util::ArrayList<sk::util::String> list;

  list.add(s);
  CPPUNIT_ASSERT(list.contains(s) == true);
  CPPUNIT_ASSERT(list.contains("bbb") == false);
  CPPUNIT_ASSERT(list.contains("abc") == false);
}

void
sk::util::test::ArrayListTest::
testRemove()
{
  sk::util::ArrayList<sk::util::String> list;
  list.add(new sk::util::String("aaa"));
  list.add(new sk::util::String("bbb"));
  list.add(new sk::util::String("ccc"));

  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL("bbb", list.get(1));

  list.remove(1);
  CPPUNIT_ASSERT_EQUAL(2, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(1));

  list.remove(1);
  CPPUNIT_ASSERT_EQUAL(1, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_THROW(list.remove(1), sk::util::IndexOutOfBoundsException);

  list.remove(0);
  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_THROW(list.remove(0), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.remove(1), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.remove(-1), sk::util::IndexOutOfBoundsException);
}

namespace {
  class NumberedString : public sk::util::String {
    public:
      NumberedString(const char* string, int number)
        : sk::util::String(string), _number(number) {}

      int getNumber() const {
        return _number;
      }

    private:
      int _number;
  };
}

void 
sk::util::test::ArrayListTest::
testSort()
{
  sk::util::ArrayList<NumberedString> list;

  list.add(new NumberedString("ccc", 2));
  list.add(new NumberedString("bbb", 1));
  list.add(new NumberedString("aaa", 3));

  list.sort();

  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(2));

  struct Ordering : public virtual sk::util::OrderingChecker<NumberedString> {
    bool isOrdered(const NumberedString& first, const NumberedString& second) const {
      return first.getNumber() < second.getNumber();
    }
  };
  list.sort(Ordering());

  CPPUNIT_ASSERT_EQUAL("bbb", list.get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(1));
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(2));
}

void 
sk::util::test::ArrayListTest::
testInspect()
{
  sk::util::ArrayList<sk::util::String> list;
  CPPUNIT_ASSERT_EQUAL("[]", list.inspect());

  list.add(new sk::util::String("aaa"));
  list.add(new sk::util::String("bbb"));

  CPPUNIT_ASSERT_EQUAL("[2: 0*\"aaa\", 1*\"bbb\" ]", list.inspect());

  sk::util::String s = "zzz";
  list.add(s);

  CPPUNIT_ASSERT_EQUAL("[3: 0*\"aaa\", 1*\"bbb\", 2&\"zzz\" ]", list.inspect());
}

void
sk::util::test::ArrayListTest::
testRemoveAll()
{
  sk::util::ArrayList<sk::util::String> list;

  list.add(new sk::util::String("aaa"));
  list.add(new sk::util::String("bbbuuu"));
  list.add(new sk::util::String("ccc"));
  list.add(new sk::util::String("ddduuu"));
  list.add(new sk::util::String("uuu"));

  CPPUNIT_ASSERT_EQUAL(5, list.size());
  struct Selector : public virtual sk::util::Selector<sk::util::String> {
    bool assess(const sk::util::String& item) const {
      return item.endsWith("uuu");
    }
  };
  CPPUNIT_ASSERT(list.removeAll(Selector()) == true);
  CPPUNIT_ASSERT_EQUAL(2, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(1));
}

void
sk::util::test::ArrayListTest::
testShuffle()
{
  sk::util::ArrayList<sk::util::String> l1;
  l1.add(new sk::util::String("aaa"));
  l1.add(new sk::util::String("bbb"));
  l1.add(new sk::util::String("ccc"));
  l1.add(new sk::util::String("ddd"));
  l1.add(new sk::util::String("eee"));
  l1.add(new sk::util::String("fff"));
  l1.add(new sk::util::String("uuu"));
  l1.add(new sk::util::String("zzz"));

  sk::util::ArrayList<sk::util::String> l2;
  l1.forEach(sk::util::CopyingProcessor<sk::util::String>(l2));

  CPPUNIT_ASSERT_EQUAL(l1.inspect(), l2.inspect());

  l2.shuffle();
  CPPUNIT_ASSERT_EQUAL(l1.size(), l2.size());
  CPPUNIT_ASSERT(l1.inspect() != l2.inspect());
}

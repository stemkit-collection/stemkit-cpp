/*  vim:sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StandardContainerTest.h"
#include <sk/util/Holder.cxx>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/CopyingProcessor.cxx>
#include <sk/util/test/Probe.cxx>

sk::util::test::collection::StandardContainerTest::
StandardContainerTest()
{
}

sk::util::test::collection::StandardContainerTest::
~StandardContainerTest()
{
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::StandardContainerTest::
makeStoringList()
{
  throw sk::util::UnsupportedOperationException("makeStoringList()");
}

void
sk::util::test::collection::StandardContainerTest::
setUp()
{
  test::Probe<String>::resetCounter();
}

void
sk::util::test::collection::StandardContainerTest::
tearDown()
{
  test::Probe<String>::resetCounter();
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerCreate()
{
  Holder<List> list(makeStoringList());

  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_EQUAL(true, list.get().isEmpty());
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerAdd()
{
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
  Holder<List> list(makeStoringList());

  test::Probe<String> p1("aaa");
  test::Probe<String> p2("bbb");
  
  list.getMutable().add(p1);
  list.getMutable().add(p2);
  list.getMutable().add(new test::Probe<String>("ccc"));

  CPPUNIT_ASSERT_EQUAL(false, list.get().isEmpty());
  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL(3, test::Probe<String>::getCounter());

  list.getMutable().clear();

  CPPUNIT_ASSERT_EQUAL(true, list.get().isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_EQUAL(2, test::Probe<String>::getCounter());
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerGet()
{
  Holder<List> list(makeStoringList());

  list.getMutable().add(new String("aaa"));
  list.getMutable().add(new String("bbb"));
  list.getMutable().add(new String("ccc"));

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(2));

  CPPUNIT_ASSERT_THROW(list.get().get(3), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerForEach()
{
  Holder<List> list(makeStoringList());
  std::vector<String> target;

  CPPUNIT_ASSERT_EQUAL(size_t(0), target.size());
  list.getMutable().add(new String("aaa"));
  list.getMutable().add(new String("zzz"));
  list.getMutable().add(new String("uuu"));

  struct Copier : public virtual sk::util::Processor<const String> {
    Copier(std::vector<String>& target) 
      : _target(target) {}

    void process(const String& item) const {
      _target.push_back(item);
    }
    std::vector<String>& _target;
  };

  list.get().forEach(Copier(target));
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
sk::util::test::collection::StandardContainerTest::
testStandardContainerFind()
{
  Holder<List> list(makeStoringList());

  list.getMutable().add(new String("aaa"));
  list.getMutable().add(new String("bbb"));
  list.getMutable().add(new String("ccc"));
  Holder<String> holder;

  CPPUNIT_ASSERT(list.get().find(holder, ExactStringSelector("zzz")) == false);
  CPPUNIT_ASSERT(list.get().find(holder, ExactStringSelector("aaa")) == true);
  CPPUNIT_ASSERT(&holder.get() == &list.get().get(0));

  CPPUNIT_ASSERT(list.get().find(holder, ExactStringSelector("ccc")) == true);
  CPPUNIT_ASSERT(&holder.get() == &list.get().get(2));

  CPPUNIT_ASSERT(list.get().find(holder, ExactStringSelector("zzz")) == false);
}

void 
sk::util::test::collection::StandardContainerTest::
testStandardContainerContains()
{
  sk::util::String s("abc");
  Holder<List> list(makeStoringList());

  list.getMutable().add(s);
  CPPUNIT_ASSERT(list.get().contains(s) == true);
  CPPUNIT_ASSERT(list.get().contains("bbb") == false);
  CPPUNIT_ASSERT(list.get().contains("abc") == false);
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerRemove()
{
  Holder<List> list(makeStoringList());
  list.getMutable().add(new sk::util::String("aaa"));
  list.getMutable().add(new sk::util::String("bbb"));
  list.getMutable().add(new sk::util::String("ccc"));

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));

  list.getMutable().remove(1);
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(1));

  list.getMutable().remove(1);
  CPPUNIT_ASSERT_EQUAL(1, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(1), sk::util::IndexOutOfBoundsException);

  list.getMutable().remove(0);
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(0), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(1), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(-1), sk::util::IndexOutOfBoundsException);
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
sk::util::test::collection::StandardContainerTest::
testStandardContainerSort()
{
  Holder<List> list(makeStoringList());

  list.getMutable().add(new NumberedString("ccc", 2));
  list.getMutable().add(new NumberedString("bbb", 1));
  list.getMutable().add(new NumberedString("aaa", 3));

  list.getMutable().sort();

  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(2));

  struct Assessor : public virtual sk::util::BinaryAssessor<String> {
    bool assess(const String& first, const String& second) const {
      return upcast<NumberedString>(first).getNumber() < upcast<NumberedString>(second).getNumber();
    }
  };
  list.getMutable().sort(Assessor());

  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(2));
}

void 
sk::util::test::collection::StandardContainerTest::
testStandardContainerInspect()
{
  Holder<List> list(makeStoringList());
  CPPUNIT_ASSERT_EQUAL("[]", list.get().inspect());

  list.getMutable().add(new sk::util::String("aaa"));
  list.getMutable().add(new sk::util::String("bbb"));

  CPPUNIT_ASSERT_EQUAL("[2: 0*\"aaa\", 1*\"bbb\" ]", list.get().inspect());

  sk::util::String s = "zzz";
  list.getMutable().add(s);

  CPPUNIT_ASSERT_EQUAL("[3: 0*\"aaa\", 1*\"bbb\", 2&\"zzz\" ]", list.get().inspect());
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerRemoveAll()
{
  Holder<List> list(makeStoringList());

  list.getMutable().add(new sk::util::String("aaa"));
  list.getMutable().add(new sk::util::String("bbbuuu"));
  list.getMutable().add(new sk::util::String("ccc"));
  list.getMutable().add(new sk::util::String("ddduuu"));
  list.getMutable().add(new sk::util::String("uuu"));

  CPPUNIT_ASSERT_EQUAL(5, list.get().size());
  struct Selector : public virtual sk::util::Selector<sk::util::String> {
    bool assess(const sk::util::String& item) const {
      return item.endsWith("uuu");
    }
  };
  CPPUNIT_ASSERT(list.getMutable().removeAll(Selector()) == true);
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(1));
}

void
sk::util::test::collection::StandardContainerTest::
testStandardContainerShuffle()
{
  Holder<List> l1(makeCopyingList());
  l1.getMutable().add("aaa");
  l1.getMutable().add("bbb");
  l1.getMutable().add("ccc");
  l1.getMutable().add("ddd");
  l1.getMutable().add("eee");
  l1.getMutable().add("fff");
  l1.getMutable().add("uuu");
  l1.getMutable().add("zzz");

  Holder<List> l2(makeStoringList());
  l1.getMutable().forEach(sk::util::CopyingProcessor<sk::util::String>(l2.getMutable()));

  CPPUNIT_ASSERT_EQUAL(l1.get().inspect(), l2.get().inspect());

  l2.getMutable().shuffle();
  CPPUNIT_ASSERT_EQUAL(l1.get().size(), l2.get().size());
  CPPUNIT_ASSERT(l1.get().inspect() != l2.get().inspect());
}

void 
sk::util::test::collection::StandardContainerTest::
testStandardContainerReverse()
{
  Holder<List> list(makeCopyingList());

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");
  list.getMutable().add("ddd");

  CPPUNIT_ASSERT_EQUAL("[4: 0*\"aaa\", 1*\"bbb\", 2*\"ccc\", 3*\"ddd\" ]", list.get().inspect());

  list.getMutable().reverse();
  CPPUNIT_ASSERT_EQUAL("[4: 0*\"ddd\", 1*\"ccc\", 2*\"bbb\", 3*\"aaa\" ]", list.get().inspect());
}

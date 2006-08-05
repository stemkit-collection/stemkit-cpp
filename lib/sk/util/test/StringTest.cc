/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringTest.h"
#include <sk/util/String.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::StringTest);

sk::util::test::StringTest::
StringTest()
{
}

sk::util::test::StringTest::
~StringTest()
{
}

void
sk::util::test::StringTest::
setUp()
{
}

void
sk::util::test::StringTest::
tearDown()
{
}

void
sk::util::test::StringTest::
testMisc()
{
  String s("xyz");

  CPPUNIT_ASSERT_EQUAL(String("sk::util::String"), s.getClass().getName());
  CPPUNIT_ASSERT_EQUAL(s, s.toString());
  CPPUNIT_ASSERT_EQUAL(0, strcmp("xyz", s.getChars()));
}

void
sk::util::test::StringTest::
testEmpty()
{
  CPPUNIT_ASSERT_EQUAL(true, String().isEmpty());
  CPPUNIT_ASSERT_EQUAL(false, String("abc").isEmpty());
  CPPUNIT_ASSERT_EQUAL(std::string(), std::string(String()));
  CPPUNIT_ASSERT_EQUAL(std::string(), std::string(String("")));

  CPPUNIT_ASSERT_EQUAL(0, String().length());
  CPPUNIT_ASSERT_EQUAL(0, String().size());
}

void
sk::util::test::StringTest::
testCreate()
{
  CPPUNIT_ASSERT_EQUAL(std::string("a"), std::string(String('a')));
  CPPUNIT_ASSERT_EQUAL(std::string("z"), std::string(String('z')));

  CPPUNIT_ASSERT_EQUAL(std::string("abcdefg"), std::string(String("abcdefg")));
  CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(String("abcdefg", 3)));
  CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(String("abc", 5)));
  CPPUNIT_ASSERT_EQUAL(3, String("abc", 5).size());

  String s("abracadabra");

  CPPUNIT_ASSERT_EQUAL(std::string("abracadabra"), std::string(String(s)));
}

void
sk::util::test::StringTest::
testSum()
{
  CPPUNIT_ASSERT_EQUAL(String("aaabbb"), String("aaa") + String("bbb"));
  CPPUNIT_ASSERT_EQUAL(String("aaa"), String("aaa") + String());
  CPPUNIT_ASSERT_EQUAL(String("aaa"), String() + String("aaa"));
  CPPUNIT_ASSERT_EQUAL(String(), String() + String());

  CPPUNIT_ASSERT_EQUAL(String("aaabbb"), String("aaa") + "bbb");
  CPPUNIT_ASSERT_EQUAL(String("aaabbb"), "aaa" + String("bbb"));

  CPPUNIT_ASSERT_EQUAL(String("aaabbb"), String("aaa") + std::string("bbb"));
  CPPUNIT_ASSERT_EQUAL(String("aaabbb"), std::string("aaa") + String("bbb"));

  CPPUNIT_ASSERT_EQUAL(String("aaab"), String("aaa") + 'b');
  CPPUNIT_ASSERT_EQUAL(String("abbb"), 'a' + String("bbb"));
}

void
sk::util::test::StringTest::
testAssignment()
{
  String s1 = "abcdefg";
  String s2 = s1;

  CPPUNIT_ASSERT_EQUAL(String("abcdefg"), s1);
  CPPUNIT_ASSERT_EQUAL(String("abcdefg"), s2);

  s1 = "zzz";
  CPPUNIT_ASSERT_EQUAL(String("zzz"), s1);
  CPPUNIT_ASSERT_EQUAL(String("abcdefg"), s2);
  
  s2 = s1;
  CPPUNIT_ASSERT_EQUAL(String("zzz"), s2);
}

void
sk::util::test::StringTest::
testTrim()
{
  CPPUNIT_ASSERT_EQUAL(String("zzz"), String("\t  zzz  \t\t").trim());
  CPPUNIT_ASSERT_EQUAL(String("cba"), String(" \r\t \ncba").strip());
}

void
sk::util::test::StringTest::
testInspect() 
{
  CPPUNIT_ASSERT_EQUAL(String("\"abcdefg\""), String("abcdefg").inspect());
  CPPUNIT_ASSERT_EQUAL(String("\"\\x01\\x8A\\r\\n\""), String("\01\x8a\015\012").inspect());
}

void
sk::util::test::StringTest::
testConstructFromStringWithLength()
{
  std::string s("abcd\0zzz", 8);
  
  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), String(s, 3).inspect());
  CPPUNIT_ASSERT_EQUAL(3, String(s, 3).length());

  CPPUNIT_ASSERT_EQUAL(4, String(s, 7).size());
  CPPUNIT_ASSERT_EQUAL(String("abcd").inspect(), String(s, 7).inspect());
}

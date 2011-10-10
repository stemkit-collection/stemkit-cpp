/*  vim: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringTest.h"
#include <sk/util/String.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/IllegalArgumentException.h>
#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <string.h>

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
  const char* empty = 0;

  CPPUNIT_ASSERT_EQUAL(true, String(empty).isEmpty());
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
  const char* s = 0;
  CPPUNIT_ASSERT_EQUAL(String("zzz"), String("\t  zzz  \t\t").trim());
  CPPUNIT_ASSERT_EQUAL(String("cba"), String(" \r\t \ncba").strip());
  CPPUNIT_ASSERT_EQUAL(String(""), String("    ").strip());
  CPPUNIT_ASSERT_EQUAL(String(""), String("").strip());
  CPPUNIT_ASSERT_EQUAL(String(""), String(s).strip());
  CPPUNIT_ASSERT_EQUAL(String("Hello, World!!!"), String("   Hello, World!!!       ").trim());
}

void
sk::util::test::StringTest::
testInspect() 
{
  CPPUNIT_ASSERT_EQUAL(String("\"abcdefg\""), String("abcdefg").inspect());
  // CPPUNIT_ASSERT_EQUAL(String("\"\\x01\\x8A\\r\\n\""), String("\01\x8a\015\012").inspect());
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

void
sk::util::test::StringTest::
testConstructFromCharsWithLength()
{
  sk::util::String s("abcdefg", 8);
  
  CPPUNIT_ASSERT_EQUAL(7, s.size());
  CPPUNIT_ASSERT_EQUAL("abcdefg", s);
}

void
sk::util::test::StringTest::
testConstructFromCharVectorWithLength()
{
  const char* chars = "abcdefg";
  std::vector<char> data(chars, chars + 7);
  sk::util::String s(&data.front(), 7);
  
  CPPUNIT_ASSERT_EQUAL(7, s.size());
  CPPUNIT_ASSERT_EQUAL("abcdefg", s);
}

void
sk::util::test::StringTest::
testStartsWith()
{
  CPPUNIT_ASSERT_EQUAL(true, String("abc").startsWith("abc"));
  CPPUNIT_ASSERT_EQUAL(true, String("abc").startsWith("ab"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").startsWith("ac"));
  CPPUNIT_ASSERT_EQUAL(true, String("abc").startsWith(""));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").startsWith("abcd"));

  CPPUNIT_ASSERT_EQUAL(false, String("aBczzz").startsWith("abc"));
  CPPUNIT_ASSERT_EQUAL(true, String("aBczzz").startsWithIgnoreCase("abc"));
  CPPUNIT_ASSERT_EQUAL(false, String("aBczzz").startsWithIgnoreCase("abz"));
}

void
sk::util::test::StringTest::
testEndsWith()
{
  CPPUNIT_ASSERT_EQUAL(true, String("abc").endsWith("abc"));
  CPPUNIT_ASSERT_EQUAL(true, String("abc").endsWith("bc"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").endsWith("ab"));
  CPPUNIT_ASSERT_EQUAL(true, String("abc").endsWith(""));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").endsWith("aabc"));

  CPPUNIT_ASSERT_EQUAL(false, String("zzzaBc").endsWith("abc"));
  CPPUNIT_ASSERT_EQUAL(true, String("zzzaBc").endsWithIgnoreCase("abc"));
  CPPUNIT_ASSERT_EQUAL(false, String("zzzaBc").endsWithIgnoreCase("abz"));
}

void
sk::util::test::StringTest::
testEquals()
{
  CPPUNIT_ASSERT_EQUAL(true, String("abc").equals("abc"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals("abcd"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals("aabc"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals("ab"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals("bc"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals("b"));
  CPPUNIT_ASSERT_EQUAL(false, String("abc").equals(""));
}

void
sk::util::test::StringTest::
testEqualsIgnoreCase()
{
  CPPUNIT_ASSERT_EQUAL(true, String("abc").equalsIgnoreCase("ABC"));
  CPPUNIT_ASSERT_EQUAL(true, String("AbC").equalsIgnoreCase("aBc"));
}

void
sk::util::test::StringTest::
testSqueeze()
{
  String s("aaabbbccc");

  CPPUNIT_ASSERT_EQUAL(String("aaabccc").inspect(), s.squeeze('b').inspect());
  CPPUNIT_ASSERT_EQUAL(String("abbbccc").inspect(), s.squeeze('a').inspect());
  CPPUNIT_ASSERT_EQUAL(String("aaabbbc").inspect(), s.squeeze('c').inspect());
}

void
sk::util::test::StringTest::
testIndex()
{
  String s("aaabbbccc");
  CPPUNIT_ASSERT_EQUAL(-1, s.indexOf('z'));
  CPPUNIT_ASSERT_EQUAL(-1, s.lastIndexOf('z'));

  CPPUNIT_ASSERT_EQUAL(0, s.indexOf('a'));
  CPPUNIT_ASSERT_EQUAL(2, s.lastIndexOf('a'));

  CPPUNIT_ASSERT_EQUAL(3, s.indexOf('b'));
  CPPUNIT_ASSERT_EQUAL(-1, s.indexOf('B'));
  CPPUNIT_ASSERT_EQUAL(3, s.indexOfIgnoreCase('B'));

  CPPUNIT_ASSERT_EQUAL(5, s.lastIndexOf('b'));
  CPPUNIT_ASSERT_EQUAL(-1, s.lastIndexOf('B'));
  CPPUNIT_ASSERT_EQUAL(5, s.lastIndexOfIgnoreCase('B'));

  CPPUNIT_ASSERT_EQUAL(6, s.indexOf('c'));
  CPPUNIT_ASSERT_EQUAL(8, s.lastIndexOf('c'));
}

void
sk::util::test::StringTest::
testSubstring()
{
  String s("aaabbbccc");

  CPPUNIT_ASSERT_EQUAL("bccc", s.substring(5));
  CPPUNIT_ASSERT_EQUAL("", s.substring(9));
  CPPUNIT_ASSERT_EQUAL("aaabbbccc", s.substring(0));
  CPPUNIT_ASSERT_THROW(s.substring(-1), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(s.substring(10), sk::util::IndexOutOfBoundsException);

  CPPUNIT_ASSERT_EQUAL("aaab", s.substring(0, 4));
  CPPUNIT_ASSERT_EQUAL("abbbc", s.substring(2, 7));
  CPPUNIT_ASSERT_EQUAL("bccc", s.substring(5, 9));
  CPPUNIT_ASSERT_EQUAL("aaabbbccc", s.substring(0, 9));
  CPPUNIT_ASSERT_EQUAL("", s.substring(5, 5));

  CPPUNIT_ASSERT_EQUAL("bbbccc", s.substring(3, -1));
  CPPUNIT_ASSERT_EQUAL("bbbcc", s.substring(3, -2));

  CPPUNIT_ASSERT_THROW(s.substring(-1, 5), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(s.substring(2, 10), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(s.substring(10, 10), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(s.substring(5, 4), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::StringTest::
testTransformations()
{
    CPPUNIT_ASSERT_EQUAL("a.c.dz", sk::util::String("a:c:dz").replace(':', '.'));
    CPPUNIT_ASSERT_EQUAL("ABCD", sk::util::String("abcd").toUpperCase());
    CPPUNIT_ASSERT_EQUAL("abcd", sk::util::String("AbCd").toLowerCase());
    CPPUNIT_ASSERT_EQUAL("ba", sk::util::String("aaa").replace("aa", "b"));

    CPPUNIT_ASSERT_EQUAL("aaaZZbcccZZb", sk::util::String("aaabbbbcccbbbb").replace("bbb", "ZZ"));
    CPPUNIT_ASSERT_EQUAL("aaaZZZZbcccZZZZb", sk::util::String("aaabbbbcccbbbb").replace("bbb", "ZZZZ"));
}

void
sk::util::test::StringTest::
testCharAt()
{
    String s("abc");
    CPPUNIT_ASSERT_EQUAL('a', s.charAt(0));
    CPPUNIT_ASSERT_EQUAL('b', s.charAt(1));
    CPPUNIT_ASSERT_EQUAL('c', s.charAt(2));

    CPPUNIT_ASSERT_THROW(s.charAt(-1), sk::util::IndexOutOfBoundsException);
    CPPUNIT_ASSERT_THROW(s.charAt(3), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::StringTest::
testContains()
{
  String s("aaabbbccc");

  CPPUNIT_ASSERT_EQUAL(true, s.contains("aaa"));
  CPPUNIT_ASSERT_EQUAL(true, s.contains("bbb"));
  CPPUNIT_ASSERT_EQUAL(true, s.contains("ccc"));

  CPPUNIT_ASSERT_EQUAL(true, s.contains(""));

  CPPUNIT_ASSERT_EQUAL(false, s.contains("aaaa"));
  CPPUNIT_ASSERT_EQUAL(false, s.contains("bbbb"));
  CPPUNIT_ASSERT_EQUAL(false, s.contains("cccc"));

  CPPUNIT_ASSERT_EQUAL(false, s.contains("AAA"));
  CPPUNIT_ASSERT_EQUAL(false, s.contains("BBB"));
  CPPUNIT_ASSERT_EQUAL(false, s.contains("CCC"));

  CPPUNIT_ASSERT_EQUAL(false, s.contains("aaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

void
sk::util::test::StringTest::
testContainsIgnoreCase()
{
  String s("aAabbBCcc");

  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("AaA"));
  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("BBB"));
  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("ccc"));

  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase(""));

  CPPUNIT_ASSERT_EQUAL(false, s.containsIgnoreCase("aAaa"));
  CPPUNIT_ASSERT_EQUAL(false, s.containsIgnoreCase("BBBb"));
  CPPUNIT_ASSERT_EQUAL(false, s.containsIgnoreCase("cccc"));

  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("AAA"));
  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("BBB"));
  CPPUNIT_ASSERT_EQUAL(true, s.containsIgnoreCase("CCC"));

  CPPUNIT_ASSERT_EQUAL(false, s.containsIgnoreCase("aaaaaaaaaaaaaaaaaaAAaaaaaa"));
}

void
sk::util::test::StringTest::
testStringIndex()
{
  String s("aaabbbccc");

  CPPUNIT_ASSERT_EQUAL(0, s.indexOf(""));
  CPPUNIT_ASSERT_EQUAL(9, s.lastIndexOf(""));

  CPPUNIT_ASSERT_EQUAL(0, s.indexOf("aaa"));
  CPPUNIT_ASSERT_EQUAL(3, s.indexOf("bbb"));
  CPPUNIT_ASSERT_EQUAL(6, s.indexOf("ccc"));

  CPPUNIT_ASSERT_EQUAL(-1, s.indexOf("accc"));

  CPPUNIT_ASSERT_EQUAL(3, s.indexOf("bb"));
  CPPUNIT_ASSERT_EQUAL(4, s.lastIndexOf("bb"));
}

void
sk::util::test::StringTest::
testValueOf()
{
  CPPUNIT_ASSERT_EQUAL("127", String::valueOf(127));
  CPPUNIT_ASSERT_EQUAL("-1", String::valueOf(-1));
  CPPUNIT_ASSERT_EQUAL("0", String::valueOf(0));
}

void 
sk::util::test::StringTest::
testMultiply()
{
  CPPUNIT_ASSERT_EQUAL("aaaaaaaaaa", sk::util::String("a") * 10);
  CPPUNIT_ASSERT_EQUAL("ababab", sk::util::String("ab") * 3);
  CPPUNIT_ASSERT_EQUAL("", sk::util::String() * 10);
  CPPUNIT_ASSERT_EQUAL("", sk::util::String("zzzzzzz") * 0);

  CPPUNIT_ASSERT_THROW(sk::util::String("zzzzzzz") * -2, sk::util::IllegalArgumentException);
}

void 
sk::util::test::StringTest::
testCompareOperators()
{
  sk::util::String sample("dddd");

  CPPUNIT_ASSERT(sample == sk::util::String("dddd"));
  CPPUNIT_ASSERT(sample != sk::util::String("ddd"));
  CPPUNIT_ASSERT(sample > sk::util::String("aaaa"));
  CPPUNIT_ASSERT(sample < sk::util::String("eeee"));
  CPPUNIT_ASSERT(sample >= sk::util::String("aaaa"));
  CPPUNIT_ASSERT(sample <= sk::util::String("eeee"));

  CPPUNIT_ASSERT(sample == "dddd");
  CPPUNIT_ASSERT(sample != "ddd");
  CPPUNIT_ASSERT(sample > "aaaa");
  CPPUNIT_ASSERT(sample < "eeee");
  CPPUNIT_ASSERT(sample >= "aaaa");
  CPPUNIT_ASSERT(sample <= "eeee");

  CPPUNIT_ASSERT(sample == std::string("dddd"));
  CPPUNIT_ASSERT(sample != std::string("ddd"));
  CPPUNIT_ASSERT(sample > std::string("aaaa"));
  CPPUNIT_ASSERT(sample < std::string("eeee"));
  CPPUNIT_ASSERT(sample >= std::string("aaaa"));
  CPPUNIT_ASSERT(sample <= std::string("eeee"));
}

void 
sk::util::test::StringTest::
testReverseCompareOperators()
{
  sk::util::String sample("dddd");

  CPPUNIT_ASSERT(std::string("dddd") == sample);
  CPPUNIT_ASSERT(std::string("ddd") != sample);
  CPPUNIT_ASSERT(std::string("aaaa") < sample);
  CPPUNIT_ASSERT(std::string("eeee") > sample);
  CPPUNIT_ASSERT(std::string("aaaa") <= sample);
  CPPUNIT_ASSERT(std::string("eeee") >= sample);

  CPPUNIT_ASSERT("dddd" == sample);
  CPPUNIT_ASSERT("ddd" != sample);
  CPPUNIT_ASSERT("aaaa" < sample);
  CPPUNIT_ASSERT("eeee" > sample);
  CPPUNIT_ASSERT("aaaa" <= sample);
  CPPUNIT_ASSERT("eeee" >= sample);
}

void
sk::util::test::StringTest::
testSplit()
{
  sk::util::Strings data;
  data = sk::util::String("aaa bbb ccc").split();

  CPPUNIT_ASSERT_EQUAL(3, data.size());
  CPPUNIT_ASSERT_EQUAL("aaa", data.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", data.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", data.get(2));
}

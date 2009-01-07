/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_CPPUNIT_STRINGASSERT_H_
#define _SK_CPPUNIT_STRINGASSERT_H_

#include <cppunit/TestAssert.h>
#include <sk/util/String.h>

CPPUNIT_NS_BEGIN

template<>
struct assertion_traits<std::string>
{
    static bool equal( const std::string& x, const std::string& y )
    {
        return sk::util::String(x).equals(y);
    }

    static std::string toString( const std::string& x )
    {
        return sk::util::String(x).inspect();
    }
};

template<>
struct assertion_traits<sk::util::String>
{
    static bool equal(const sk::util::String& x, const sk::util::String& y)
    {
        return x.equals(y);
    }

    static std::string toString(const sk::util::String& x)
    {
        return x.inspect();
    }
};

void assertEquals(const char* expected,  const char* actual, SourceLine sourceLine, const std::string& message)
{
    if(expected == 0 && actual != 0) {
        Asserter::failNotEqual("<null_ptr>", sk::util::String(actual).inspect(), sourceLine, message);
    }
    else if(expected != 0 && actual == 0) {
        Asserter::failNotEqual(sk::util::String(expected).inspect(), "<null_ptr>", sourceLine, message);
    }
    else if(expected != 0 && actual != 0) {
        assertEquals(sk::util::String(expected), sk::util::String(actual), sourceLine, message);
    }
}

void assertEquals(const char* expected,  const std::string& actual, SourceLine sourceLine, const std::string& message)
{
    assertEquals(expected, actual.c_str(), sourceLine, message);
}

void assertEquals(const std::string& expected,  const char* actual, SourceLine sourceLine, const std::string& message)
{
    assertEquals(expected.c_str(), actual, sourceLine, message);
}

void assertEquals(const std::string& expected,  const std::string& actual, SourceLine sourceLine, const std::string& message)
{
    assertEquals(expected.c_str(), actual.c_str(), sourceLine, message);
}

CPPUNIT_NS_END

#endif /* _SK_CPPUNIT_STRINGASSERT_H_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/cppunit/StringAssert.h>
#include <iostream>

CPPUNIT_NS_BEGIN

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

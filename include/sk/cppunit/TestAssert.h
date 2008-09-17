/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_CPPUNIT_TESTASSERT_H_
#define _SK_CPPUNIT_TESTASSERT_H_

#include <cppunit/TestAssert.h>
#include <sk/util/String.h>

CPPUNIT_NS_BEGIN

void assertEquals(const std::string& expected, const sk::util::String& actual, SourceLine sourceLine, const std::string &message)
{
    assertEquals(sk::util::String(expected).inspect(), actual.inspect(), sourceLine, message);
}

CPPUNIT_NS_END

#endif /* _SK_CPPUNIT_TESTASSERT_H_ */

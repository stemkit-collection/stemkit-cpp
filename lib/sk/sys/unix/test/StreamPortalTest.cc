/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "StreamPortalTest.h"
#include <sk/sys/StreamPortal.h>
#include <sk/io/FileDescriptorProvider.h>
#include <sk/io/FileDescriptor.h>
#include <sk/util/Properties.h>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::StreamPortalTest);

sk::sys::test::StreamPortalTest::
StreamPortalTest()
{
}

sk::sys::test::StreamPortalTest::
~StreamPortalTest()
{
}

void
sk::sys::test::StreamPortalTest::
setUp()
{
}

void
sk::sys::test::StreamPortalTest::
tearDown()
{
}

void
sk::sys::test::StreamPortalTest::
testStreams()
{
  CPPUNIT_ASSERT_EQUAL(45, ::dup2(1, 45));
  CPPUNIT_ASSERT_EQUAL(55, ::dup2(1, 55));
  CPPUNIT_ASSERT_EQUAL(65, ::dup2(1, 65));
  {
    sk::util::Properties registry;
    registry.setProperty("SK_STREAMS", "45|55|65");

    sk::sys::StreamPortal portal(registry);
    CPPUNIT_ASSERT_EQUAL(3, portal.size());
    CPPUNIT_ASSERT_EQUAL("", portal.getProperty("SK_STREAMS"));

    CPPUNIT_ASSERT_EQUAL(45, sk::util::upcast<sk::io::FileDescriptorProvider>(portal.getStream(0)).getFileDescriptor().getFileNumber());
    CPPUNIT_ASSERT_EQUAL(55, sk::util::upcast<sk::io::FileDescriptorProvider>(portal.getStream(1)).getFileDescriptor().getFileNumber());
    CPPUNIT_ASSERT_EQUAL(65, sk::util::upcast<sk::io::FileDescriptorProvider>(portal.getStream(2)).getFileDescriptor().getFileNumber());
  }
  CPPUNIT_ASSERT_EQUAL(-1, ::close(45));
  CPPUNIT_ASSERT_EQUAL(-1, ::close(55));
  CPPUNIT_ASSERT_EQUAL(-1, ::close(65));
}

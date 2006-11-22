/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PtyTest.h"
#include <sk/io/Pty.h>
#include <sk/io/DataInputStream.h>
#include <sk/util/Container.h>

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::PtyTest);

sk::io::test::PtyTest::
PtyTest()
{
}

sk::io::test::PtyTest::
~PtyTest()
{
}

void
sk::io::test::PtyTest::
setUp()
{
}

void
sk::io::test::PtyTest::
tearDown()
{
}

void
sk::io::test::PtyTest::
testMasterSlavePipe()
{
  sk::io::Pty pty;
  sk::io::DataInputStream data(pty.getMasterSlavePipe().inputStream());
  sk::io::DataInputStream echo(pty.getSlaveMasterPipe().inputStream());

  pty.getMasterSlavePipe().outputStream().write(sk::util::Container("Hello\n"));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello\n").inspect(), data.readLine().inspect());

  pty.getSlaveMasterPipe().outputStream().write(sk::util::Container("Hi\n"));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello\r\n").inspect(), echo.readLine().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hi\r\n").inspect(), echo.readLine().inspect());
}

void
sk::io::test::PtyTest::
testSlaveMasterPipe()
{
  sk::io::Pty pty;
  sk::io::DataInputStream data(pty.getSlaveMasterPipe().inputStream());

  pty.getSlaveMasterPipe().outputStream().write(sk::util::Container("Hello\n"));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello\r\n").inspect(), data.readLine().inspect());
}

void 
sk::io::test::PtyTest::
testSlaveTty()
{
  sk::io::Pty pty;
  CPPUNIT_ASSERT_EQUAL(1, isatty(pty.getMasterSlavePipe().inputStream().getFileDescriptor().getFileNumber()));
}

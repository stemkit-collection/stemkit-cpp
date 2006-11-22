/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PtyProcessTest.h"
#include <sk/sys/PtyProcess.h>
#include <sk/io/DataInputStream.h>
#include <sk/util/Container.h>

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::PtyProcessTest);

sk::sys::test::PtyProcessTest::
PtyProcessTest()
{
}

sk::sys::test::PtyProcessTest::
~PtyProcessTest()
{
}

void
sk::sys::test::PtyProcessTest::
setUp()
{
}

void
sk::sys::test::PtyProcessTest::
tearDown()
{
}

void
sk::sys::test::PtyProcessTest::
testTranslate()
{
  PtyProcess process(sk::util::StringArray("tr") + "a" + "A");
  sk::io::DataInputStream data(process.inputStream());

  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.outputStream().write(sk::util::Container("abcdaaa\n"));
  process.outputStream().write('\04');

  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdaaa\r\n").inspect(), data.readLine().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("AbcdAAA\r\n").inspect(), data.readLine().inspect());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PtyProcessTest::
testTty()
{
  PtyProcess process(sk::util::StringArray("tty"));
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
  CPPUNIT_ASSERT_EQUAL((process.getPtyName() + "\r\n").inspect(), data.readLine().inspect());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PtyProcessTest::
testSu()
{
  PtyProcess process(sk::util::StringArray("su") + "root" + "-c" + "id");
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sleep(1);
  process.outputStream().write(sk::util::Container("zzz\r"));
  data.readLine();
  data.readLine();
  // CPPUNIT_ASSERT_EQUAL(sk::util::String("").inspect(), data.readLine().inspect());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}


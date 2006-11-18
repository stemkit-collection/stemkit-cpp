/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipeProcessTest.h"
#include <sk/sys/PipeProcess.h>
#include <sk/io/DataInputStream.h>
#include <sk/util/Container.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::PipeProcessTest);

sk::sys::test::PipeProcessTest::
PipeProcessTest()
{
}

sk::sys::test::PipeProcessTest::
~PipeProcessTest()
{
}

void
sk::sys::test::PipeProcessTest::
setUp()
{
}

void
sk::sys::test::PipeProcessTest::
tearDown()
{
}

void
sk::sys::test::PipeProcessTest::
testTranslate()
{
  PipeProcess process(sk::util::StringArray("tr") + "a" + "A");
  sk::io::DataInputStream data(process.inputStream());

  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.outputStream().write(sk::util::Container("abcdaaa\n"));
  process.outputStream().close();

  CPPUNIT_ASSERT_EQUAL(sk::util::String("AbcdAAA\n").inspect(), data.readLine().inspect());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipeProcessTest.h"
#include <sk/sys/PipeProcess.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>
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

void
sk::sys::test::PipeProcessTest::
testDataNoErrors()
{
  PipeProcess process(sk::util::StringArray("echo") + "it's" + "a" + "world");
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  CPPUNIT_ASSERT_THROW(process.inputErrorStream().read(), sk::io::EOFException);
  CPPUNIT_ASSERT_EQUAL(sk::util::String("it's a world\n").inspect(), data.readLine().inspect());

  process.join();

  CPPUNIT_ASSERT_EQUAL(0, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testErrorsNoData()
{
  PipeProcess process(sk::util::StringArray("sh") + "-c" + "echo 'some error' 1>&2");
  sk::io::DataInputStream errors(process.inputErrorStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  CPPUNIT_ASSERT_THROW(process.inputStream().read(), sk::io::EOFException);
  CPPUNIT_ASSERT_EQUAL(sk::util::String("some error\n").inspect(), errors.readLine().inspect());

  process.join();

  CPPUNIT_ASSERT_EQUAL(0, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testArguments()
{
  PipeProcess process(sk::util::StringArray("printf") + "1: '%s', 2: '%s'" + "aaa" + "bbb ccc");
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("1: 'aaa', 2: 'bbb ccc'").inspect(), data.readLine().inspect());

  process.join();
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

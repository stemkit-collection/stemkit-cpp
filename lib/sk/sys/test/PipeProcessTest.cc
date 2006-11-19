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

void
sk::sys::test::PipeProcessTest::
testErrorsAfterJoin()
{
  PipeProcess process(sk::util::StringArray("sh") + "-c" + "exec 1>&2; echo Error1; echo Error2");
  process.join();

  CPPUNIT_ASSERT_EQUAL(2, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Error1\n").inspect(), process.errors().get(0).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("Error2\n").inspect(), process.errors().get(1).inspect());
}

void
sk::sys::test::PipeProcessTest::
testAlltogether()
{
  PipeProcess process(
    sk::util::StringArray("sh") + "-c" + "while read line; do echo GOOD: ${line}; echo BAD: ${line} 1>&2; done"
  );
  sk::io::DataInputStream data(process.inputStream());
  sk::io::DataInputStream errors(process.inputErrorStream());

  process.outputStream().write(sk::util::Container("first\n"));
  process.outputStream().write(sk::util::Container("second\n"));
  process.outputStream().close();

  CPPUNIT_ASSERT_EQUAL(sk::util::String("GOOD: first\n").inspect(), data.readLine().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("GOOD: second\n").inspect(), data.readLine().inspect());
  CPPUNIT_ASSERT_THROW(data.readLine(), sk::io::EOFException);

  CPPUNIT_ASSERT_EQUAL(sk::util::String("BAD: first\n").inspect(), errors.readLine().inspect());
      
  process.join();
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());

  CPPUNIT_ASSERT_EQUAL(1, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("BAD: second\n").inspect(), process.errors().get(0).inspect());
}

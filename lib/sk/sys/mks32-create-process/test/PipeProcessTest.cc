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
#include <sk/io/ClosedChannelException.h>
#include <sk/util/Container.h>
#include <sk/io/FileInputStream.h>

#include <sk/cppunit/SourcePath.h>
#include <unistd.h>

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
  PipeProcess process(sk::util::Strings("ruby") + "-e" + "puts readline.tr('a', 'A')");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.outputStream().write(sk::util::Container("abcdaaa\n"));
  process.outputStream().close();

  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL("AbcdAAA", data.readLine().trim());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testDataNoErrors()
{
  PipeProcess process(sk::util::Strings("ruby") + "-e" + "puts 'Hello, world'");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_THROW(process.inputErrorStream().read(), sk::io::EOFException);
  CPPUNIT_ASSERT_EQUAL("Hello, world", data.readLine().trim());

  process.join();

  CPPUNIT_ASSERT_EQUAL(0, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testErrorsNoData()
{
  PipeProcess process(sk::util::Strings("ruby") + "-e" + "$stderr.puts 'some error'");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sk::io::DataInputStream errors(process.inputErrorStream());
  CPPUNIT_ASSERT_THROW(process.inputStream().read(), sk::io::EOFException);
  CPPUNIT_ASSERT_EQUAL("some error", errors.readLine().trim());

  process.join();

  CPPUNIT_ASSERT_EQUAL(0, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testArguments()
{
  PipeProcess process(sk::util::Strings("ruby") + "-e" + "puts ARGV.inspect" + "aaa" + "bbb ccc");
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  CPPUNIT_ASSERT_EQUAL("[\"aaa\", \"bbb ccc\"]", data.readLine().trim());

  process.join();
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PipeProcessTest::
testErrorsAfterJoin()
{
  PipeProcess process(sk::util::Strings("ruby") + "-e" + "$stderr.puts :Error1, :Error2");
  process.join();

  CPPUNIT_ASSERT_EQUAL(2, process.errors().size());
  CPPUNIT_ASSERT_EQUAL("Error1", process.errors().get(0).trim());
  CPPUNIT_ASSERT_EQUAL("Error2", process.errors().get(1).trim());
}

void
sk::sys::test::PipeProcessTest::
testAlltogether()
{
  PipeProcess process(sk::util::Strings("ruby") + "-ne" + "$stdout.puts 'GOOD: ' + $_; $stderr.puts 'BAD: ' + $_");

  sk::io::DataInputStream data(process.inputStream());
  sk::io::DataInputStream errors(process.inputErrorStream());

  process.outputStream().write(sk::util::Container("first\n"));
  process.outputStream().write(sk::util::Container("second\n"));
  process.outputStream().close();

  CPPUNIT_ASSERT_EQUAL("GOOD: first", data.readLine().trim());
  CPPUNIT_ASSERT_EQUAL("GOOD: second", data.readLine().trim());
  CPPUNIT_ASSERT_THROW(data.readLine(), sk::io::EOFException);

  CPPUNIT_ASSERT_EQUAL("BAD: first", errors.readLine().trim());

  process.join();
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());

  CPPUNIT_ASSERT_EQUAL(1, process.errors().size());
  CPPUNIT_ASSERT_EQUAL("BAD: second", process.errors().get(0).trim());
}

void
sk::sys::test::PipeProcessTest::
testInputRedirect()
{
  sk::io::FileInputStream input(sk::cppunit::SourcePath::make("test-data"));
  PipeProcess process(input, sk::util::Strings("ruby") + "-ne" + "puts $_.tr('a', 'A')");
  sk::io::DataInputStream data(process.inputStream());

  CPPUNIT_ASSERT_THROW(process.outputStream().write('a'), sk::io::ClosedChannelException);
  CPPUNIT_ASSERT_EQUAL("Line1: AAA", data.readLine().trim());
  CPPUNIT_ASSERT_EQUAL("Line2: bbb", data.readLine().trim());
  CPPUNIT_ASSERT_EQUAL("Line3: ccc", data.readLine().trim());
  CPPUNIT_ASSERT_THROW(data.readLine(), sk::io::EOFException);

  process.join();
  CPPUNIT_ASSERT_EQUAL(0, process.errors().size());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PtyProcessTest.h"
#include <sk/sys/PtyProcess.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>
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
  PtyProcess process(sk::util::Strings("tr") + "a" + "A");
  sk::io::DataInputStream data(process.inputStream());

  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.outputStream().write(sk::util::Container("abcdaaa\n"));
  process.outputStream().write('\04');

  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdaaa\r\n").inspect(), data.readLine().inspect());

  sk::util::String result = data.readLine();

  if(result.at(0) == '^') {
    CPPUNIT_ASSERT_EQUAL(sk::util::String("^D\010\010AbcdAAA\r\n").inspect(), result.inspect());
  }
  else if(result.at(0) == '\04') {
    CPPUNIT_ASSERT_EQUAL(sk::util::String("\004AbcdAAA\r\n").inspect(), result.inspect());
  }
  else {
    CPPUNIT_ASSERT_EQUAL(sk::util::String("AbcdAAA\r\n").inspect(), result.inspect());
  }

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PtyProcessTest::
testTty()
{
  PtyProcess process(sk::util::Strings("tty"));
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, data.readLine().trim().endsWith(process.getPty().getName()));

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::PtyProcessTest::
testSu()
{
  PtyProcess process(sk::util::Strings("su") + "root" + "-c" + "id");
  sk::io::DataInputStream data(process.inputStream());
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  std::cerr << "PTY: " << process.getPty().getName() << std::endl;
  while(true) {
    char c = process.inputStream().read();
    std::cerr << "C: " << c << std::endl;
    if(c == ':') {
      break;
    }
  }
  // process.outputStream().write(sk::util::Container("root\n"));

  try {
    while(true) {
      std::cerr << "L: " << data.readLine().inspect() << std::endl;
    }
  }
  catch(const sk::io::EOFException& exception) {}

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}


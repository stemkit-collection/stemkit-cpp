/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AnonymousPipeTest.h"

#include <sk/util/String.h>
#include <sk/util/Container.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/OutputStream.h>
#include <sk/io/InputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include <signal.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::AnonymousPipeTest);

sk::io::test::AnonymousPipeTest::
AnonymousPipeTest()
{
}

sk::io::test::AnonymousPipeTest::
~AnonymousPipeTest()
{
}

void
sk::io::test::AnonymousPipeTest::
setUp()
{
}

void
sk::io::test::AnonymousPipeTest::
tearDown()
{
  signal(SIGPIPE, SIG_DFL);
}

void
sk::io::test::AnonymousPipeTest::
testCreate()
{
  AnonymousPipe pipe;
}

void
sk::io::test::AnonymousPipeTest::
testReadWrite()
{
  AnonymousPipe pipe;

  pipe.outputStream().write(sk::util::Container("abcdefg\n"));

  DataInputStream data(pipe.inputStream());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abcdefg\n").inspect(), data.readLine().inspect());
}

void
sk::io::test::AnonymousPipeTest::
testCloseOutput()
{
  AnonymousPipe pipe;

  pipe.closeOutput();
  CPPUNIT_ASSERT_THROW(pipe.inputStream().read(), sk::io::EOFException);
}

void
sk::io::test::AnonymousPipeTest::
testCloseInput()
{
  AnonymousPipe pipe;

  pipe.closeInput();
  signal(SIGPIPE, SIG_IGN);
  CPPUNIT_ASSERT_THROW(pipe.outputStream().write(0), sk::io::IOException);
}

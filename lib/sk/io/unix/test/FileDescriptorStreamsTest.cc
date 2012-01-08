/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileDescriptorStreamsTest.h"
#include <sk/util/SystemException.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/io/EOFException.h>
#include <sk/util/Holder.cxx>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileDescriptorStreamsTest);

sk::io::test::FileDescriptorStreamsTest::
FileDescriptorStreamsTest()
{
}

sk::io::test::FileDescriptorStreamsTest::
~FileDescriptorStreamsTest()
{
}

void
sk::io::test::FileDescriptorStreamsTest::
setUp()
{
  int fds[2];
  if(pipe(fds) != 0) {
    throw sk::util::SystemException("pipe() failed");
  }
  _inputStreamHolder.set(new sk::io::FileDescriptorInputStream(fds[0]));
  _outputStreamHolder.set(new sk::io::FileDescriptorOutputStream(fds[1]));
  _dataInputStreamHolder.set(new sk::io::DataInputStream(_inputStreamHolder.getMutable()));
  _dataOutputStreamHolder.set(new sk::io::DataOutputStream(_outputStreamHolder.getMutable()));
}

void
sk::io::test::FileDescriptorStreamsTest::
tearDown()
{
  _dataInputStreamHolder.clear();
  _dataOutputStreamHolder.clear();

  _inputStreamHolder.clear();
  _outputStreamHolder.clear();

}

void
sk::io::test::FileDescriptorStreamsTest::
testReadWrite()
{
  dataOutput().writeInt(1234);
  CPPUNIT_ASSERT_EQUAL(uint32_t(1234), dataInput().readInt());

  dataOutput().writeChars("Hello\n");
  CPPUNIT_ASSERT_EQUAL(sk::util::String("\"Hello\\n\""), dataInput().readLine().inspect());
}

void
sk::io::test::FileDescriptorStreamsTest::
testClose()
{
  output().close();
  CPPUNIT_ASSERT_THROW(dataInput().readChar(), sk::io::EOFException);
}

void
sk::io::test::FileDescriptorStreamsTest::
testCloseOnDestruction()
{
  _outputStreamHolder.clear();
  CPPUNIT_ASSERT_THROW(dataInput().readChar(), sk::io::EOFException);
}

void
sk::io::test::FileDescriptorStreamsTest::
testPartialReadOnEof()
{
  dataOutput().writeChars("Hello, it's me");
  output().close();

  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello, it's me"), dataInput().readLine());
  CPPUNIT_ASSERT_THROW(dataInput().readChar(), sk::io::EOFException);
}

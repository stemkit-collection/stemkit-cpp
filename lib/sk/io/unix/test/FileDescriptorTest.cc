/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileDescriptorTest.h"
#include <sk/util/SystemException.h>
#include <sk/io/EOFException.h>
#include <sk/util/Holder.cxx>
#include <unistd.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileDescriptorTest);

sk::io::test::FileDescriptorTest::
FileDescriptorTest()
{
}

sk::io::test::FileDescriptorTest::
~FileDescriptorTest()
{
}

void
sk::io::test::FileDescriptorTest::
setUp()
{
  int fds[2];
  if(pipe(fds) != 0) {
    throw sk::util::SystemException("pipe() failed");
  }
  _readDescriptor.set(new sk::io::FileDescriptor(fds[0]));
  _writeDescriptor.set(new sk::io::FileDescriptor(fds[1]));
}

void
sk::io::test::FileDescriptorTest::
tearDown()
{
  _writeDescriptor.clear();
  _readDescriptor.clear();
}

void
sk::io::test::FileDescriptorTest::
testClone()
{
  sk::io::FileDescriptor fd = input();
  input().close();

  char c = 'a';
  output().write(&c, 0, 1);

  char buffer[80];
  fd.read(buffer, 0, 1);

  CPPUNIT_ASSERT_EQUAL('a', buffer[0]);
  output().close();
  CPPUNIT_ASSERT_THROW(fd.read(buffer, 0, 1), sk::io::EOFException);
}

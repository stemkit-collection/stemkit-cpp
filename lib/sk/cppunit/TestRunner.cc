/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SingleLineOutputter.h>

#include <stdlib.h>

sk::cppunit::TestRunner::
TestRunner()
{
  if(getenv("VIMRUNTIME") != 0) {
    setOutputter(new sk::cppunit::SingleLineOutputter(*this));
  }
}

sk::cppunit::TestRunner::
~TestRunner()
{
}

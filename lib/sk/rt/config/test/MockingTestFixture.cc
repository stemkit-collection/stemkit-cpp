/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "MockingTestFixture.h"
#include <sk/rt/config/SpotLocator.h>
#include <sstream>
#include <iostream>

sk::rt::config::test::MockingTestFixture::
MockingTestFixture()
{
}

sk::rt::config::test::MockingTestFixture::
~MockingTestFixture()
{
}

void
sk::rt::config::test::MockingTestFixture::
setUp()
{
  SpotLocator::setStreamOpener(*this);
}

void
sk::rt::config::test::MockingTestFixture::
tearDown()
{
  SpotLocator::clearStreamOpener();
}

std::istream*
sk::rt::config::test::MockingTestFixture::
openStream(const sk::util::Pathname& name) const
{
  return new std::istringstream(name.toString());
}

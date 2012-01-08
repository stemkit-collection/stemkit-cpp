/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/cppunit/SourcePath.h>
#include <stdlib.h>

sk::util::String sk::cppunit::SourcePath::_base;

sk::cppunit::SourcePath::
SourcePath()
{
}

sk::cppunit::SourcePath::
~SourcePath()
{
}

const sk::util::Class
sk::cppunit::SourcePath::
getClass() const
{
  return sk::util::Class("sk::cppunit::SourcePath");
}

void
sk::cppunit::SourcePath::
setBase(const sk::util::String& path)
{
  _base = path;
}

const sk::util::String
sk::cppunit::SourcePath::
make(const sk::util::String& file)
{
  if(_base.empty() == true) {
    _base = getenv("JAM_SRCDIR");
  }
  const sk::util::String name = file.trim();
  return _base.empty() || name.at(0) == '/' ? name : _base + '/' + name;
}

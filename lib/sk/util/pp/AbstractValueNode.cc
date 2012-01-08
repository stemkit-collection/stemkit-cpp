/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "AbstractValueNode.h"

static const sk::util::String __className("sk::util::pp::AbstractValueNode");

sk::util::pp::AbstractValueNode::
AbstractValueNode()
  : _start(0), _end(0)
{
}

sk::util::pp::AbstractValueNode::
AbstractValueNode(const std::vector<char>& data, int start, int end)
  : _value(&data.front() + start, end - start), _start(start), _end(end)
{
}

sk::util::pp::AbstractValueNode::
~AbstractValueNode()
{
}

const sk::util::Class
sk::util::pp::AbstractValueNode::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::pp::AbstractValueNode::
toString() const
{
  return _value.trim();
}

int
sk::util::pp::AbstractValueNode::
startPosition() const
{
  return _start;
}

int
sk::util::pp::AbstractValueNode::
endPosition() const
{
  return _end;
}

void
sk::util::pp::AbstractValueNode::
output(const Configurator& /*configurator*/, const sk::util::String& /*indent*/, std::ostream& stream) const
{
  stream << _value;
}

bool
sk::util::pp::AbstractValueNode::
isGonnaBreak() const
{
  return false;
}

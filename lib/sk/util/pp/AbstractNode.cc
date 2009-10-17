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

#include "AbstractNode.h"

static const sk::util::String __className("sk::util::pp::AbstractNode");

sk::util::pp::AbstractNode::
AbstractNode()
  : _start(0), _end(0)
{
}

sk::util::pp::AbstractNode::
AbstractNode(const std::vector<char>& data, int start, int end)
  : _value(&data.front() + start, end - start), _start(start), _end(end)
{
}

sk::util::pp::AbstractNode::
~AbstractNode()
{
}

const sk::util::Class
sk::util::pp::AbstractNode::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::pp::AbstractNode::
toString() const
{
  return _value;
}

int 
sk::util::pp::AbstractNode::
startPosition() const
{
  return _start;
}

int 
sk::util::pp::AbstractNode::
endPosition() const
{
  return _end;
}

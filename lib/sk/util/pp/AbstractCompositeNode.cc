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

#include "AbstractCompositeNode.h"

static const sk::util::String __className("sk::util::pp::AbstractCompositeNode");

sk::util::pp::AbstractCompositeNode::
AbstractCompositeNode()
  : _start(0), _end(0)
{
}

sk::util::pp::AbstractCompositeNode::
AbstractCompositeNode(const std::vector<char>& data, int start)
  : _start(start), _end(0)
{
}

sk::util::pp::AbstractCompositeNode::
~AbstractCompositeNode()
{
}

const sk::util::Class
sk::util::pp::AbstractCompositeNode::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::util::pp::AbstractCompositeNode::
setNode(sk::util::pp::Node* node)
{
  _nodeHolder.set(node);
  if(_nodeHolder.isEmpty() == false) {
    return _nodeHolder.get().endPosition() - _nodeHolder.get().startPosition();
  }
  return 0;
}

int 
sk::util::pp::AbstractCompositeNode::
startPosition() const
{
  return _start;
}

int 
sk::util::pp::AbstractCompositeNode::
endPosition() const
{
  return _end;
}

void 
sk::util::pp::AbstractCompositeNode::
setLength(int length)
{
  _end = _start + length;
}

const sk::util::String
sk::util::pp::AbstractCompositeNode::
inspect() const
{
  if(_nodeHolder.isEmpty() == true) {
    return "empty";
  }
  return _nodeHolder.get().inspect();
}

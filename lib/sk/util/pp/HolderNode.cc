/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Holder.cxx>

#include "HolderNode.h"
#include "PrimeNode.h"

static const sk::util::String __className("sk::util::pp::HolderNode");

sk::util::pp::HolderNode::
HolderNode(const std::vector<char>& data, int start)
  : _start(start), _end(0), _kind(0)
{
}

sk::util::pp::HolderNode::
HolderNode()
  : _start(0), _end(0), _kind(0)
{
}

sk::util::pp::HolderNode::
~HolderNode()
{
}

const sk::util::Class
sk::util::pp::HolderNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::HolderNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0) {
    return 0;
  }
  sk::util::Holder<HolderNode> nodeHolder(new HolderNode(data, offset));
  int index = 0;
  bool inside = false;
  while((index + offset) < data.size()) {
    if(index > 0 && inside == false) {
      break;
    }
    char item = data[(index++) + offset];
    switch(item) {
      case '(':
        if(inside == true) {
          return 0;
        }
        inside = true;
        continue;

      case ')':
        if(inside == true) {
          nodeHolder.get().setLength(index);
          return nodeHolder.deprive();
        }
        break;

      case '*':
      case '&':
        index += nodeHolder.get().setNode(item, PrimeNode().parse(data, offset + index, sk::util::Container(")")));
        continue;

      default:
        if(isspace(item) == true) {
          continue;
        }
    }
    break;
  }
  return 0;
}

void 
sk::util::pp::HolderNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('(');
}

int 
sk::util::pp::HolderNode::
startPosition() const
{
  return _start;
}

int 
sk::util::pp::HolderNode::
endPosition() const
{
  return _end;
}

void 
sk::util::pp::HolderNode::
setLength(int length)
{
  _end = _start + length;
}

const sk::util::String
sk::util::pp::HolderNode::
inspect() const 
{
  if(_nodeHolder.isEmpty() == true) {
    return "<HolderNode: empty>";
  }
  return sk::util::String("<HolderNode: ") + _kind + _nodeHolder.get().inspect() + ">";
}

int 
sk::util::pp::HolderNode::
setNode(char kind, sk::util::pp::Node* node)
{
  _nodeHolder.set(node);
  if(_nodeHolder.isEmpty() == false) {
    _kind = kind;
    return _nodeHolder.get().endPosition() - _nodeHolder.get().startPosition();
  }
  _kind = 0;
  return 0;
}

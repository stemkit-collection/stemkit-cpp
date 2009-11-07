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
#include <sk/util/NullPointerException.h>
#include <sk/util/inspect.h>

#include "SlotNode.h"
#include "PrimeNode.h"

static const sk::util::String __className("sk::util::pp::SlotNode");

sk::util::pp::SlotNode::
SlotNode()
{
}

sk::util::pp::SlotNode::
SlotNode(const std::vector<char>& data, int start, sk::util::pp::Node* node)
  : AbstractCompositeNode(data, start)
{
  if(node == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  addNode(node);
  setLength(node->endPosition() - start);
  _prefix = sk::util::String(&data.front() + start, node->startPosition() - start);
}

sk::util::pp::SlotNode::
~SlotNode()
{
}

const sk::util::Class
sk::util::pp::SlotNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::SlotNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0) {
    return 0;
  }
  for(int index=0; (index + offset) < data.size(); ++index) {
    char item = data[index + offset];
    switch(item) {
      case '*':
      case '&':
      case '=': {
        Node* node = PrimeNode().parse(data, offset + index + 1, terminators);
        if(node != 0) {
          return new SlotNode(data, offset, node);
        }
        break;
      }
      default:
        if(isdigit(item)) {
          continue;
        }
    }
    break;
  }
  return 0;
}

void
sk::util::pp::SlotNode::
pushOpenBraket(std::vector<char>& brakets) const
{
}

const sk::util::String
sk::util::pp::SlotNode::
inspect() const
{
  return _prefix + AbstractCompositeNode::inspect();
}

void 
sk::util::pp::SlotNode::
output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream) const
{
  stream << _prefix;
  getNode(0).output(configurator, indent, stream);
}

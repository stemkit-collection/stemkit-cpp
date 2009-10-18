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
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include "CollectionNode.h"
#include "SlotNode.h"

static const sk::util::String __className("sk::util::pp::CollectionNode");

sk::util::pp::CollectionNode::
CollectionNode()
{
}

sk::util::pp::CollectionNode::
CollectionNode(const std::vector<char>& data, int start)
  : AbstractCompositeNode(data, start)
{
}

sk::util::pp::CollectionNode::
~CollectionNode()
{
}

const sk::util::Class
sk::util::pp::CollectionNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::CollectionNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0) {
    return 0;
  }
  sk::util::Holder<CollectionNode> nodeHolder(new CollectionNode(data, offset));
  bool inside = false;
  for(int index=0; (index + offset) < data.size(); ++index) {
    if(index > 0 && inside == false) {
      break;
    }
    char item = data[index + offset];
    switch(item) {
      case '[':
        if(inside == true) {
          return 0;
        }
        inside = true;
        continue;

      case ']':
        if(inside == true) {
          nodeHolder.get().setLength(index + 1);
          return nodeHolder.deprive();
        }
        break;

      case ',':
        continue;

      default:
        if(isspace(item) == true) {
          continue;
        }
        int length = nodeHolder.get().addNode(SlotNode().parse(data, offset + index, sk::util::Container(",]")));
        if(length > 0) {
          index += length - 1;
          continue;
        }
    }
    break;
  }
  return 0;
}

void 
sk::util::pp::CollectionNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('[');
}

const sk::util::String
sk::util::pp::CollectionNode::
inspect() const
{
  return "<CollectionNode: " + AbstractCompositeNode::inspect() + ">";
}

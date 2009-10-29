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

#include "StructNode.h"
#include "NamedNode.h"

static const sk::util::String __className("sk::util::pp::StructNode");

sk::util::pp::StructNode::
StructNode()
{
}

sk::util::pp::StructNode::
StructNode(const std::vector<char>& data, int start)
  : AbstractCompositeNode(data, start)
{
}

sk::util::pp::StructNode::
~StructNode()
{
}

const sk::util::Class
sk::util::pp::StructNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::StructNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& /*terminators*/) const
{
  if(offset < 0) {
    return 0;
  }
  sk::util::Holder<StructNode> nodeHolder(new StructNode(data, offset));
  bool inside = false;
  bool gotname = false;
  for(int index=0; (index + offset) < data.size(); ++index) {
    if(index > 0 && inside == false) {
      break;
    }
    char item = data[index + offset];
    switch(item) {
      case '<':
        if(inside == true) {
          return 0;
        }
        inside = true;
        continue;

      case '>':
        if(inside == true && gotname == true) {
          nodeHolder.get().setLength(index + 1);
          return nodeHolder.deprive();
        }
        break;

      default:
        if(gotname == false) {
          if(item == ':') {
            nodeHolder.get().setName(sk::util::String(&data.front() + offset + 1, index - 1));
            gotname = true;
            continue;
          }
          if(isalnum(item)) {
            continue;
          }
          break;
        }
        if(item == ',' || isspace(item)) {
          continue;
        }
        int length = nodeHolder.get().addNode(NamedNode().parse(data, offset + index, sk::util::Container(",>")));
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
sk::util::pp::StructNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('<');
}

void 
sk::util::pp::StructNode::
setName(const sk::util::String& name)
{
  _name = name;
}

const sk::util::String
sk::util::pp::StructNode::
inspect() const
{
  return "<StructNode:" + _name + ": " + AbstractCompositeNode::inspect() + ">";
}

void 
sk::util::pp::StructNode::
output(const sk::util::String& indent, std::ostream& stream) const
{
  stream << '<'<< _name << ": ";
  AbstractCompositeNode::output(indent, stream, hasBreakingNode());
  stream << '>';
}

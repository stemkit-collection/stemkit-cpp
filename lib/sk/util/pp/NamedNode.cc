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
#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>
#include <sk/util/NullPointerException.h>

#include "NamedNode.h"
#include "TextNode.h"
#include "PrimeNode.h"

static const sk::util::String __className("sk::util::pp::NamedNode");

sk::util::pp::NamedNode::
NamedNode()
{
}

sk::util::pp::NamedNode::
NamedNode(const std::vector<char>& data, int start, const sk::util::String& name, sk::util::pp::Node* node)
  : AbstractCompositeNode(data, start), _name(name)
{
  if(node == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  addNode(node);
  setLength(node->endPosition() - start);
}

sk::util::pp::NamedNode::
~NamedNode()
{
}

const sk::util::Class
sk::util::pp::NamedNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::NamedNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0) {
    return 0;
  }
  for(int index=0; (index + offset) < data.size(); ++index) {
    char item = data[index + offset];
    if(isspace(item) == true) {
      continue;
    }
    sk::util::Container terms(terminators);
    terms += "=";

    sk::util::Holder<Node> nameHolder(TextNode().parse(data, offset + index, terms));
    if(nameHolder.isEmpty() == false) {
      index += nameHolder.get().endPosition() - nameHolder.get().startPosition();
      if(((index + offset) < data.size()) && data[index + offset] == '=') {
        Node* node = PrimeNode().parse(data, offset + index + 1, terminators);
        if(node != 0) {
          return new NamedNode(data, offset, nameHolder.get().toString(), node);
        }
      }
    }
    break;
  }
  return 0;
}

void
sk::util::pp::NamedNode::
pushOpenBraket(std::vector<char>& brakets) const
{
}

const sk::util::String
sk::util::pp::NamedNode::
inspect() const
{
  return _name + "=" + AbstractCompositeNode::inspect();
}

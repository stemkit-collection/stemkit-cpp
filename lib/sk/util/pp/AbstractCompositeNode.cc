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
#include <sk/util/ArrayList.cxx>

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
addNode(sk::util::pp::Node* node)
{
  if(node != 0) {
    _nodes.add(node);
    return node->endPosition() - node->startPosition();
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
  if(_nodes.isEmpty() == true) {
    return "empty";
  }
  sk::util::StringArray depot;
  struct InspectingProcessor : public virtual sk::util::Processor<Node> {
    InspectingProcessor(sk::util::StringArray& depot)
      : _depot(depot) {}

    void process(Node& node) const {
      _depot << node.inspect();
    }
    sk::util::StringArray& _depot;
  };
  _nodes.forEach(InspectingProcessor(depot));
  return depot.join(", ");
}

void 
sk::util::pp::AbstractCompositeNode::
forEachNode(const sk::util::Processor<sk::util::pp::Node>& processor) const 
{
  _nodes.forEach(processor);
}

void 
sk::util::pp::AbstractCompositeNode::
output(const sk::util::String& indent, std::ostream& stream) const
{
  struct Printer : public virtual sk::util::Processor<Node> {
    Printer(const sk::util::String& indent, std::ostream& stream)
      : _indent(indent), _stream(stream) {}

    void process(Node& node) const {
      _stream << _indent;
      node.output(_indent, _stream);
      _stream << std::endl;
    }
    const sk::util::String& _indent;
    std::ostream& _stream;
  };
  forEachNode(Printer(indent, stream));
}

const sk::util::pp::Node& 
sk::util::pp::AbstractCompositeNode::
getNode(int index) const
{
  return _nodes.get(index);
}

int
sk::util::pp::AbstractCompositeNode::
getNodeCount() const
{
  return _nodes.size();
}

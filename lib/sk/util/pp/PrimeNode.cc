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
#include <sk/util/ArrayList.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include "PrimeNode.h"
#include "StructNode.h"
#include "CollectionNode.h"
#include "HolderNode.h"
#include "PointerNode.h"
#include "TextNode.h"

static const sk::util::String __className("sk::util::pp::PrimeNode");

sk::util::pp::PrimeNode::
PrimeNode()
{
  _parsers.add(new PointerNode());
  // _parsers.add(new StructNode());
  _parsers.add(new CollectionNode());
  _parsers.add(new HolderNode());
  _parsers.add(new TextNode());
}

sk::util::pp::PrimeNode::
~PrimeNode()
{
}

const sk::util::Class
sk::util::pp::PrimeNode::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct Invocator : public virtual sk::util::Processor<sk::util::pp::Parser> {
    Invocator(const std::vector<char>& data, int offset, const std::vector<char>& terminators)
      : _data(data), _offset(offset), _terminators(terminators) {}

    void process(sk::util::pp::Parser& parser) const {
      sk::util::pp::Node* node = parser.parse(_data, _offset, _terminators);
      if(node) {
        throw node;
      }
      parser.pushOpenBraket(_terminators);
    }
    const std::vector<char>& _data;
    mutable std::vector<char> _terminators;
    const int _offset;
  };
}

sk::util::pp::Node* 
sk::util::pp::PrimeNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  try {
    _parsers.forEach(Invocator(data, offset, terminators));
  }
  catch(sk::util::pp::Node* node) {
    return node;
  }
  return 0;
}

void 
sk::util::pp::PrimeNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  struct OpenBraketPusher : public virtual sk::util::Processor<sk::util::pp::Parser> {
    OpenBraketPusher(std::vector<char>& brakets)
      : _brakets(brakets) {}

    void process(sk::util::pp::Parser& parser) const {
      parser.pushOpenBraket(_brakets);
    }
    std::vector<char>& _brakets;
  };
  _parsers.forEach(OpenBraketPusher(brakets));
}

int 
sk::util::pp::PrimeNode::
startPosition() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::util::pp::PrimeNode::
endPosition() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

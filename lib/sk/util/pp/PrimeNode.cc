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
#include "StringNode.h"
#include "TextNode.h"

static const sk::util::String __className("sk::util::pp::PrimeNode");

sk::util::pp::PrimeNode::
PrimeNode()
{
  _parsers.add(new StructNode());
  _parsers.add(new CollectionNode());
  _parsers.add(new HolderNode());
  _parsers.add(new PointerNode());
  _parsers.add(new StringNode());
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

sk::util::pp::Node* 
sk::util::pp::PrimeNode::
parse(const std::vector<char>& data, int offset) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

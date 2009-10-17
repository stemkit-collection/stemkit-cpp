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

#include "PointerNode.h"

static const sk::util::String __className("sk::util::pp::PointerNode");

sk::util::pp::PointerNode::
PointerNode()
{
}

sk::util::pp::PointerNode::
~PointerNode()
{
}

const sk::util::Class
sk::util::pp::PointerNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::PointerNode::
parse(const std::vector<char>& data, int offset) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

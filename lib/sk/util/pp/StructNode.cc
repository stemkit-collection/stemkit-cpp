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

#include "StructNode.h"

static const sk::util::String __className("sk::util::pp::StructNode");

sk::util::pp::StructNode::
StructNode()
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
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  return 0;
}

void 
sk::util::pp::StructNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('<');
}

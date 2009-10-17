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
#include <algorithm>

#include "PointerNode.h"

static const sk::util::String __className("sk::util::pp::PointerNode");

sk::util::pp::PointerNode::
PointerNode()
{
}

sk::util::pp::PointerNode::
PointerNode(const std::vector<char>& data, int start, int end)
  : AbstractNode(data, start, end)
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
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  const sk::util::String null("<null>");
  int end = offset + null.size();
  if(offset >= 0 && end <= data.size()) {
    if(std::equal(data.begin() + offset, data.begin() + end, null.getChars()) == true) {
      return new PointerNode(data, offset, end);
    }
  }
  return 0;
}

void 
sk::util::pp::PointerNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('<');
}


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

#include "StringNode.h"

static const sk::util::String __className("sk::util::pp::StringNode");

sk::util::pp::StringNode::
StringNode()
{
}

sk::util::pp::StringNode::
StringNode(const std::vector<char>& data, int start, int end)
  : AbstractNode(data, start, end)
{
}

sk::util::pp::StringNode::
~StringNode()
{
}

const sk::util::Class
sk::util::pp::StringNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::StringNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0 || offset >= data.size() || data[offset] != '"') {
    return 0;
  }
  bool escaped = false;
  for(int index=1; (index + offset) < data.size(); ++index) {
    char item = tolower(data[index + offset]);
    if(escaped == true) {
      escaped = false;
      continue;
    }
    if(item == '\\') {
      escaped = true;
      continue;
    }
    if(item == '"') {
      return new StringNode(data, offset, index + offset + 1);
    }
  }
  return 0;
}

void 
sk::util::pp::StringNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('"');
}

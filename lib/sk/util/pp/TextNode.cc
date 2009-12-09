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

#include "TextNode.h"
#include <algorithm>

static const sk::util::String __className("sk::util::pp::TextNode");

sk::util::pp::TextNode::
TextNode()
{
}

sk::util::pp::TextNode::
TextNode(const std::vector<char>& data, int start, int end)
  : AbstractValueNode(data, start, end)
{
}

sk::util::pp::TextNode::
~TextNode()
{
}

const sk::util::Class
sk::util::pp::TextNode::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::pp::Node* 
sk::util::pp::TextNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const
{
  if(offset < 0) {
    return 0;
  }
  bool escaped = false;
  bool quoted = false;
  int index = 0;
  while((index + offset) < data.size()) {
    char item = tolower(data[(index++) + offset]);
    if(escaped == true) {
      escaped = false;
      continue;
    }
    if(quoted == false) {
      if(std::find(terminators.begin(), terminators.end(), item) != terminators.end()) {
        if(!(item == '"' && index == 1)) {
          --index;
          break;
        }
      }
    }
    if(item == '\\') {
      escaped = true;
      continue;
    }
    if(item == '"') {
      if(quoted == true) {
        quoted = false;
      }
      else {
        quoted = true;
      }
    }
  }
  if(index != 0 && quoted == false && escaped == false) {
    return new TextNode(data, offset, index + offset);
  }
  return 0;
}

void 
sk::util::pp::TextNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('"');
}

const sk::util::String
sk::util::pp::TextNode::
inspect() const
{
  return "<TextNode: " + toString().inspect() + ">";
}

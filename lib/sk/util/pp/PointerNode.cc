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
  : AbstractValueNode(data, start, end)
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

namespace {
  bool checkNull(const std::vector<char>& data, int offset, int& end) {
    const sk::util::String null("<null>");
    end = offset + null.size();

    if(end <= data.size()) {
      if(std::equal(data.begin() + offset, data.begin() + end, null.getChars()) == true) {
        return true;
      }
    }
    return false;
  }

  bool checkGeneric(const std::vector<char>& data, int offset, int& end) {
    for(int index=0; (index + offset) < data.size(); ++index) {
      char item = tolower(data[index + offset]);
      switch(index) {
        case 0:
          if(item == '<') {
            continue;
          }
          break;

        case 1:
          if(item == '0') {
            continue;
          }
          break;

        case 2:
          if(item == 'x') {
            continue;
          }
          break;

        default:
          if(item == '>') {
            if(index == 3) {
              break;
            }
            end = index + offset + 1;
            return true;
          }
          if((item >= '0' && item <= '9') || (item >= 'a' && item <= 'f')) {
            continue;
          }
      }
      break;
    }
    return false;
  }
}

sk::util::pp::Node*
sk::util::pp::PointerNode::
parse(const std::vector<char>& data, int offset, const std::vector<char>& /*terminators*/) const
{
  int end = 0;

  if(offset < 0) {
    return 0;
  }
  if(checkNull(data, offset, end) == false) {
    if(checkGeneric(data, offset, end) == false) {
      return 0;
    }
  }
  return new PointerNode(data, offset, end);
}

void
sk::util::pp::PointerNode::
pushOpenBraket(std::vector<char>& brakets) const
{
  brakets.push_back('<');
}

const sk::util::String
sk::util::pp::PointerNode::
inspect() const
{
  return "<PointerNode: " + toString() + ">";
}

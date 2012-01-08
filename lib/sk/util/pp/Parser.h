/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_PARSER_H_
#define _SK_UTIL_PP_PARSER_H_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace util {
    namespace pp {
      class Node;

      class Parser
        : public virtual sk::util::Object
      {
        public:
          virtual Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const = 0;
          virtual void pushOpenBraket(std::vector<char>& brakets) const = 0;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_PARSER_H_ */

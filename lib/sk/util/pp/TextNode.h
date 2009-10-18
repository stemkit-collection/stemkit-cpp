/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_TEXTNODE_H_
#define _SK_UTIL_PP_TEXTNODE_H_

#include "AbstractValueNode.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class TextNode 
        : public sk::util::pp::AbstractValueNode,
          public virtual sk::util::pp::Parser
      {
        public:
          TextNode();
          TextNode(const std::vector<char>& data, int start, int end);
          virtual ~TextNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const;
          void pushOpenBraket(std::vector<char>& brakets) const;

        private:
          TextNode(const TextNode& other);
          TextNode& operator = (const TextNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_TEXTNODE_H_ */

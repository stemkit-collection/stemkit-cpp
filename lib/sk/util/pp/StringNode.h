/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_STRINGNODE_H_
#define _SK_UTIL_PP_STRINGNODE_H_

#include "Node.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class StringNode 
        : public virtual sk::util::pp::Node,
          public virtual sk::util::pp::Parser
      {
        public:
          StringNode();
          virtual ~StringNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset) const;

        private:
          StringNode(const StringNode& other);
          StringNode& operator = (const StringNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_STRINGNODE_H_ */

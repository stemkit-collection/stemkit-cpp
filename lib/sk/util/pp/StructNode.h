/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_STRUCTNODE_H_
#define _SK_UTIL_PP_STRUCTNODE_H_

#include "AbstractCompositeNode.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class StructNode 
        : public sk::util::pp::AbstractCompositeNode,
          public virtual sk::util::pp::Parser
      {
        public:
          StructNode();
          StructNode(const std::vector<char>& data, int start);
          virtual ~StructNode();

          void setName(const sk::util::String& name);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const;
          void pushOpenBraket(std::vector<char>& brakets) const;

        private:
          StructNode(const StructNode& other);
          StructNode& operator = (const StructNode& other);

          sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_STRUCTNODE_H_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_HOLDERNODE_H_
#define _SK_UTIL_PP_HOLDERNODE_H_

#include "Node.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class HolderNode 
        : public virtual sk::util::pp::Node,
          public virtual sk::util::pp::Parser
      {
        public:
          HolderNode();
          HolderNode(const std::vector<char>& data, int start);
          virtual ~HolderNode();

          void setLength(int length);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const;
          void pushOpenBraket(std::vector<char>& brakets) const;
          int startPosition() const;
          int endPosition() const;

        private:
          HolderNode(const HolderNode& other);
          HolderNode& operator = (const HolderNode& other);

          int _start;
          int _end;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_HOLDERNODE_H_ */

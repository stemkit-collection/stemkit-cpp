/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_ATTRIBUTENODE_H_
#define _SK_UTIL_PP_ATTRIBUTENODE_H_

#include "Node.h"

namespace sk {
  namespace util {
    namespace pp {
      class AttributeNode 
        : public virtual sk::util::pp::Node
      {
        public:
          AttributeNode();
          virtual ~AttributeNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          AttributeNode(const AttributeNode& other);
          AttributeNode& operator = (const AttributeNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_ATTRIBUTENODE_H_ */

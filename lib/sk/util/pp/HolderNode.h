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

namespace sk {
  namespace util {
    namespace pp {
      class HolderNode 
        : public virtual sk::util::pp::Node
      {
        public:
          HolderNode();
          virtual ~HolderNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          HolderNode(const HolderNode& other);
          HolderNode& operator = (const HolderNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_HOLDERNODE_H_ */
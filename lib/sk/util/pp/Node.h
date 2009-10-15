/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_NODE_H_
#define _SK_UTIL_PP_NODE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace pp {
      class Node 
        : public virtual sk::util::Object
      {
        public:
          Node();
          virtual ~Node();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Node(const Node& other);
          Node& operator = (const Node& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_NODE_H_ */

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_POINTERNODE_H_
#define _SK_UTIL_PP_POINTERNODE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace pp {
      class PointerNode 
        : public virtual sk::util::Object
      {
        public:
          PointerNode();
          virtual ~PointerNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          PointerNode(const PointerNode& other);
          PointerNode& operator = (const PointerNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_POINTERNODE_H_ */

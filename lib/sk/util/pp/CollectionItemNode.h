/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_COLLECTIONITEMNODE_H_
#define _SK_UTIL_PP_COLLECTIONITEMNODE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace pp {
      class CollectionItemNode 
        : public virtual sk::util::Object
      {
        public:
          CollectionItemNode();
          virtual ~CollectionItemNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          CollectionItemNode(const CollectionItemNode& other);
          CollectionItemNode& operator = (const CollectionItemNode& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PP_COLLECTIONITEMNODE_H_ */

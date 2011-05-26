/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_JSON_BOOLEANITEM_H_
#define _SK_RT_JSON_BOOLEANITEM_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace json {
      class BooleanItem 
        : public virtual sk::util::Object
      {
        public:
          BooleanItem();
          virtual ~BooleanItem();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          BooleanItem(const BooleanItem& other);
          BooleanItem& operator = (const BooleanItem& other);
      };
    }
  }
}

#endif /* _SK_RT_JSON_BOOLEANITEM_H_ */

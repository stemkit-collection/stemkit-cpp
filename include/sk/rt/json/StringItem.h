/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_STRINGITEM_H_
#define _SK_RT_JSON_STRINGITEM_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace json {
      class StringItem 
        : public virtual sk::util::Object
      {
        public:
          StringItem();
          virtual ~StringItem();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          StringItem(const StringItem& other);
          StringItem& operator = (const StringItem& other);
      };
    }
  }
}

#endif /* _SK_RT_JSON_STRINGITEM_H_ */

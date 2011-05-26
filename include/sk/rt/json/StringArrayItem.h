/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_STRINGARRAYITEM_H_
#define _SK_RT_JSON_STRINGARRAYITEM_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace json {
      class StringArrayItem 
        : public virtual sk::util::Object
      {
        public:
          StringArrayItem();
          virtual ~StringArrayItem();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          StringArrayItem(const StringArrayItem& other);
          StringArrayItem& operator = (const StringArrayItem& other);
      };
    }
  }
}

#endif /* _SK_RT_JSON_STRINGARRAYITEM_H_ */

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

#include <sk/rt/json/Item.h>

namespace sk {
  namespace rt {
    namespace json {
      class StringItem 
        : public sk::rt::json::Item
      {
        public:
          StringItem(const Json::Value& value, const sk::util::String& name);
          virtual ~StringItem();
      
          const sk::util::String& get();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          StringItem(const StringItem& other);
          StringItem& operator = (const StringItem& other);

          sk::util::String _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_STRINGITEM_H_ */

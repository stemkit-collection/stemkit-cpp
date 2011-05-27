/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_INTEGERITEM_H_
#define _SK_RT_JSON_INTEGERITEM_H_

#include <sk/rt/json/Item.h>

namespace sk {
  namespace rt {
    namespace json {
      class IntegerItem 
        : public sk::rt::json::Item
      {
        public:
          IntegerItem(Json::Value& value, const sk::util::String& name);
          virtual ~IntegerItem();

          int get();
          void set(const int value);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          IntegerItem& operator = (const IntegerItem& other);

          int _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_INTEGERITEM_H_ */

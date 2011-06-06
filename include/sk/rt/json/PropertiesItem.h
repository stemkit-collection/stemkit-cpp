/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_PROPERTIESITEM_H_
#define _SK_RT_JSON_PROPERTIESITEM_H_

#include <sk/rt/json/Item.h>
#include <sk/util/Properties.h>

namespace sk {
  namespace rt {
    namespace json {
      class PropertiesItem 
        : public sk::rt::json::Item
      {
        public:
          PropertiesItem(Json::Value& value, const sk::util::String& name);
          virtual ~PropertiesItem();
      
          const sk::util::Properties& get() const;
          void set(const sk::util::Properties& value);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          PropertiesItem& operator = (const PropertiesItem& other);

          mutable sk::util::Properties _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_PROPERTIESITEM_H_ */

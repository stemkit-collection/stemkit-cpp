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

#include <sk/rt/json/Item.h>
#include <sk/util/Strings.h>

namespace sk {
  namespace rt {
    namespace json {
      class StringArrayItem 
        : public sk::rt::json::Item
      {
        public:
          StringArrayItem(Json::Value& value, const sk::util::String& name);
          virtual ~StringArrayItem();
      
          const sk::util::Strings& get() const;
          void set(const sk::util::Strings& value);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          StringArrayItem& operator = (const StringArrayItem& other);

          mutable sk::util::Strings _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_STRINGARRAYITEM_H_ */

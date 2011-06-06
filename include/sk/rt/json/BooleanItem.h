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

#include <sk/rt/json/Item.h>

namespace sk {
  namespace rt {
    namespace json {
      class BooleanItem 
        : public sk::rt::json::Item
      {
        public:
          BooleanItem(Json::Value& value, const sk::util::String& name);
          virtual ~BooleanItem();
      
          bool get() const;
          void set(const bool value);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          BooleanItem& operator = (const BooleanItem& other);

          mutable bool _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_BOOLEANITEM_H_ */

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
#include <sk/util/Strings.h>

namespace sk {
  namespace rt {
    namespace json {
      class StringItem
        : public sk::rt::json::Item
      {
        public:
          StringItem(Json::Value& value, const sk::util::String& name);
          virtual ~StringItem();

          const sk::util::String& get() const;
          void set(const sk::util::String& value);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          StringItem& operator = (const StringItem& other);

          mutable sk::util::String _value;
      };
    }
  }
}

#endif /* _SK_RT_JSON_STRINGITEM_H_ */

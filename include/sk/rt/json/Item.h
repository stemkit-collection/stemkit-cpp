/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_ITEM_H_
#define _SK_RT_JSON_ITEM_H_

#include <sk/util/Object.h>
#include <sk/other/jsoncpp/json/json.h>

namespace sk {
  namespace rt {
    namespace json {
      class Item 
        : public virtual sk::util::Object
      {
        public:
          Item(Json::Value& params, const sk::util::String& name);
          virtual ~Item();

          bool isPresent() const;
          const sk::util::String& name() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        protected:
          const Json::Value& getValue() const;
          void setValue(const Json::Value& value);
          bool isObtained() const;
          void ensureAvailable() const;
          void raiseArgumentException(const std::exception& exception) const;
      
        private:
          Item& operator = (const Item& other);

          Json::Value& _params;
          const sk::util::String _name;
          mutable bool _obtained;
          mutable bool _available;
      };
    }
  }
}

#endif /* _SK_RT_JSON_ITEM_H_ */

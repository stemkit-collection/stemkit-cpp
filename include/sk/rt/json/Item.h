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
          Item(const Json::Value& root, const sk::util::String& name);
          virtual ~Item();

          bool isPresent();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        protected:
          const Json::Value& getValue();
          bool isObtained() const;
          void ensureAvailable() const;
          void raiseArgumentException(const std::exception& exception) const;
      
        private:
          Item(const Item& other);
          Item& operator = (const Item& other);

          const Json::Value& _root;
          const sk::util::String _name;
          bool _obtained;
          bool _available;
      };
    }
  }
}

#endif /* _SK_RT_JSON_ITEM_H_ */

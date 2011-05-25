/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_ACTION_ITEM_H_
#define _SK_RT_ACTION_ITEM_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace action {
      class Item 
        : public virtual sk::util::Object
      {
        public:
          Item(const sk::util::String& label);
          virtual ~Item();

          const sk::util::String& getLabel() const;
          virtual void invoke() const = 0;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Item(const Item& other);
          Item& operator = (const Item& other);

          const sk::util::String _label;
      };
    }
  }
}

#endif /* _SK_RT_ACTION_ITEM_H_ */

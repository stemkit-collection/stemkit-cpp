/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_METHOD_H_
#define _SK_UTIL_METHOD_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Class;

    class Method 
      : public virtual sk::util::Object
    {
      public:
        Method(const sk::util::String& name, const sk::util::Class& scope, bool instance);
        virtual ~Method();

        const sk::util::String getName() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Method& operator = (const Method& other);

        const sk::util::String _name;
        const sk::util::String _scopeName;
        bool _instance;
    };
  }
}

#endif /* _SK_UTIL_METHOD_H_ */

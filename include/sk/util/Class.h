/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_CLASS_
#define _SK_UTIL_CLASS_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Method;

    class Class
      : public virtual sk::util::Object 
    {
      public:
        Class(const sk::util::String& name);
        virtual ~Class();
        
        const sk::util::String getName() const;
        const sk::util::Method getMethod(const sk::util::String& name) const;
        const sk::util::Method getClassMethod(const sk::util::String& name) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
        const sk::util::String inspect() const;
      
      private:
        Class& operator = (const Class& other);

        const sk::util::String _name;
    };
  }
}

#endif /* _SK_UTIL_CLASS_ */

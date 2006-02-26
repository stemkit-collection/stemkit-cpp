/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INTEGER_
#define _SK_UTIL_INTEGER_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Integer
      : public virtual sk::util::Object 
    {
      public:
        Integer();
        virtual ~Integer();

        static const String& toString(int value);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
      
      private:
        Integer(const Integer& other);
        Integer& operator = (const Integer& other);
    };
  }
}

#endif /* _SK_UTIL_INTEGER_ */

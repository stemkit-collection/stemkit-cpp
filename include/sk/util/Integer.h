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
        Integer(int value);
        virtual ~Integer();

        char byteValue() const;
        int intValue() const;
        short shortValue() const;
        int64_t longValue() const;
        float floatValue() const;
        double doubleValue() const;

        static const String toString(int value);
        static const String toString(int value, int radix);
        static int parseInt(const sk::util::String& value);
        static int parseInt(const sk::util::String& value, int radix);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
      
      private:
        Integer& operator = (const Integer& other);

        int _value;
    };
  }
}

#endif /* _SK_UTIL_INTEGER_ */

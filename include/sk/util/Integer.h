/*  vi: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
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
        /// Constructs a newly allocated Integer object that represents the
        /// specified int value.
        Integer(int value);
        virtual ~Integer();

        /// Returns the value of this Integer as a byte.
        char byteValue() const;

        /// Returns the value of this Integer as an int.
        int intValue() const;

        /// Returns the value of this Integer as a short.
        short shortValue() const;

        /// Returns the value of this Integer as a long.
        int64_t longValue() const;

        /// Returns the value of this Integer as a float.
        float floatValue() const;

        /// Returns the value of this Integer as a double.
        double doubleValue() const;

        /// Returns a String object representing the specified integer.
        static const String toString(int value);

        /// Returns a string representation of the first argument in the radix
        /// specified by the second argument.
        static const String toString(int value, int radix);

        /// Parses the string argument as a signed decimal integer.
        static int parseInt(const sk::util::String& value);

        /// Parses the string argument as a signed integer in the radix
        /// specified by the second argument.
        static int parseInt(const sk::util::String& value, int radix);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;

        /// Returns a String object representing this Integer's value.
        const sk::util::String toString() const;
      
      private:
        Integer& operator = (const Integer& other);

        int _value;
    };
  }
}

#endif /* _SK_UTIL_INTEGER_ */

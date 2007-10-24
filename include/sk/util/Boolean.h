/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_BOOLEAN_
#define _SK_UTIL_BOOLEAN_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class String;

    class Boolean
      : public virtual sk::util::Object 
    {
      public:
        Boolean(bool value);
        explicit Boolean(const sk::util::String& value);
        virtual ~Boolean();

        bool booleanValue() const;
        const sk::util::String toString() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        static bool parseBoolean(const sk::util::String& value);

        static const Boolean& valueOf(bool value);
        static const Boolean& valueOf(const sk::util::String& value);
        static const Boolean& valueOf(const char* value);
        static const sk::util::String toString(bool value);

        static const Boolean B_TRUE;
        static const Boolean B_FALSE;

      private:
        bool _value;
    };
  }
}

#endif /* _SK_UTIL_BOOLEAN_ */

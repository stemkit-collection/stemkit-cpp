/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRINGARRAY_
#define _SK_UTIL_STRINGARRAY_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

namespace sk {
  namespace util {
    class StringArray
      : public std::vector<sk::util::String>,
        public virtual sk::util::Object 
    {
      public:
        StringArray();
        StringArray(const sk::util::String& item);
        StringArray(const char* item);
        virtual ~StringArray();

        const sk::util::String& get(int index) const;
        int size() const;
        sk::util::StringArray operator + (const sk::util::String& item) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_STRINGARRAY_ */

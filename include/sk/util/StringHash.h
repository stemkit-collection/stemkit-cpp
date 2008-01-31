/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRINGHASH_
#define _SK_UTIL_STRINGHASH_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <map>

namespace sk {
  namespace util {
    class StringHash
      : public std::map<sk::util::String, sk::util::String>,
        public virtual sk::util::Object 
    {
      public:
        StringHash();
        virtual ~StringHash();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
    };
  }
}

#endif /* _SK_UTIL_STRINGHASH_ */

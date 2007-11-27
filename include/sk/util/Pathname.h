/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_PATHNAME_
#define _SK_UTIL_PATHNAME_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Pathname
      : public virtual sk::util::Object 
    {
      public:
        Pathname(const sk::util::String& component);
        virtual ~Pathname();

        Pathname& front(const sk::util::String& component);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Pathname& operator = (const Pathname& other);

        sk::util::String _collector;
    };
  }
}

#endif /* _SK_UTIL_PATHNAME_ */

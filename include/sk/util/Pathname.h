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
        Pathname(const sk::util::String& component, const sk::util::String& defaultExtension);
        virtual ~Pathname();

        bool isAbsolute() const;
        const sk::util::String basename() const;
        const sk::util::String dirname() const;

        Pathname& front(const sk::util::String& component);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
        
      private:
        Pathname& operator = (const Pathname& other);

        void normalizePrepended(const sk::util::String& trimmedComponent);

        sk::util::String _pathname;
    };
  }
}

#endif /* _SK_UTIL_PATHNAME_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_COMPOUNDEXCEPTION_H_
#define _SK_UTIL_COMPOUNDEXCEPTION_H_

#include <sk/util/Exception.h>
#include <sk/util/List.h>

namespace sk {
  namespace util {
    class CompoundException 
      : public sk::util::Exception
    {
      public:
        CompoundException(const sk::util::List<sk::util::Exception>& exceptions);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        static const sk::util::Strings makeClassNames(const sk::util::String& label, const sk::util::List<sk::util::Exception>& exceptions);
    };
  }
}

#endif /* _SK_UTIL_COMPOUNDEXCEPTION_H_ */

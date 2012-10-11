/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STANDARDEXCEPTION_H_
#define _SK_UTIL_STANDARDEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class StandardException 
      : public sk::util::Exception
    {
      public:
        StandardException(const sk::util::Strings& strings, const std::exception& exception);
        StandardException(const std::exception& exception);
        ~StandardException() throw() {};
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_STANDARDEXCEPTION_H_ */

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_EXCEPTIONPROXY_H_
#define _SK_UTIL_EXCEPTIONPROXY_H_

#include <sk/util/Exception.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class ExceptionProxy 
      : public sk::util::Exception
    {
      public:
        ExceptionProxy(const sk::util::Strings& strings, sk::util::Exception& exception);
        ExceptionProxy(const sk::util::Strings& strings, std::exception& exception);
        ExceptionProxy(const sk::util::Strings& strings);
        virtual ~ExceptionProxy() throw();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        const sk::util::String _originalClassName;
    };
  }
}

#endif /* _SK_UTIL_EXCEPTIONPROXY_H_ */

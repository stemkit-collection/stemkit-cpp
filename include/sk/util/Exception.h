/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_EXCEPTION_
#define _SK_UTIL_EXCEPTION_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <exception>

namespace sk {
  namespace util {
    class Exception
      : public std::exception,
        public virtual sk::util::Object 
    {
      public:
        Exception(const util::String& message);
        virtual ~Exception() throw();

        const sk::util::String getMessage() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // std::exception implementation.
        const char* what() const throw();

      protected:
        const String join(const String& s1, const String& s2) const;

      private:
        sk::util::String _message;
    };
  }
}

#endif /* _SK_UTIL_EXCEPTION_ */

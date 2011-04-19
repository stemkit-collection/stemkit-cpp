/*  vim: set sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
        Exception(const util::String& message, sk::util::Exception& exception);
        Exception(const util::String& message, const std::exception& exception);
        Exception(const util::String& message, const sk::util::Strings& strings);
        virtual ~Exception() throw();

        const sk::util::String getMessage() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;

        // std::exception implementation.
        const char* what() const throw();

        template<typename S, typename T, typename TMF>
        static void guard(const S& stream, T& target, TMF method, const char* spot = 0);
        
      protected:
        const String join(const String& s1, const String& s2) const;
        const String join(const String& s1, int i1) const;

      private:
        sk::util::String _message;
    };
  }
}

template<typename S, typename T, typename TMF>
void 
sk::util::Exception::
guard(const S& stream, T& target, TMF method, const char* spot) 
{
  try {
    (target.*method)();
  }
  catch(const std::exception& exception) {
    if(spot != 0) {
      stream << spot << ": ";
    }
    stream << exception.what();
  }
  catch(...) {
    if(spot != 0) {
      stream << spot << ": ";
    }
    stream << "Unknown exception";
  }
}

#endif /* _SK_UTIL_EXCEPTION_ */

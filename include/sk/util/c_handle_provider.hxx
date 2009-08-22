/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_C_HANDLE_PROVIDER_HXX_
#define _SK_UTIL_C_HANDLE_PROVIDER_HXX_

#include <string>

namespace sk {
  namespace util {
    template<typename T, typename H>
    class c_handle_provider 
    {
      public:
        c_handle_provider(T& object);
        ~c_handle_provider();
    
        H* get_c_handle();
        const H* get_c_handle() const;
    
        static char* copy(const std::string& s, char* buffer, int size);

      private:
        c_handle_provider<T, H>& operator = (const c_handle_provider<T, H>& other);
        c_handle_provider(const c_handle_provider<T, H>& other);

        H* _handle;
    };
  }
}

#endif /* _SK_UTIL_C_HANDLE_PROVIDER_HXX_ */

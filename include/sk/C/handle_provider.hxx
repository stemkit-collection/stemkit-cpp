/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_HANDLE_PROVIDER_HXX_
#define _SK_C_HANDLE_PROVIDER_HXX_

#include <string>

namespace sk {
  namespace C {
    template<typename T, typename H>
    class handle_provider
    {
      public:
        handle_provider(T& object);
        ~handle_provider();

        H* get_c_handle();
        const H* get_c_handle() const;

      private:
        handle_provider<T, H>& operator = (const handle_provider<T, H>& other);
        handle_provider(const handle_provider<T, H>& other);

        H* _handle;
    };
  }
}

#endif /* _SK_C_HANDLE_PROVIDER_HXX_ */

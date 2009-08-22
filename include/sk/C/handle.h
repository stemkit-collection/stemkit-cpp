/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_HANDLE_H_
#define _SK_C_HANDLE_H_

#if defined(__cplusplus)

#include <sk/util/String.h>

namespace sk {
  namespace C {
    struct handle 
    {
      handle();
      static char* copy(const std::string& s, char* buffer, int size);

      bool error;
      const char* signature;
      sk::util::String errorType;
      sk::util::String errorMessage;
    };
  }
}

extern "C" {
#endif

int sk_c_handle_isError(void* handle);
int sk_c_handle_isGood(void* handle);

const char* sk_c_handle_errorType(void* handle, char* buffer, int size);
const char* sk_c_handle_errorMessage(void* handle, char* buffer, int size);

#if defined(__cplusplus)
}
#endif

#endif /* _SK_C_HANDLE_H_ */

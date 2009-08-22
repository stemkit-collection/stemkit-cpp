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

struct sk_c_handle;

#if defined(__cplusplus)
extern "C" {
#endif

int sk_c_handle_isError(const struct sk_c_handle* handle);
int sk_c_handle_isGood(const struct sk_c_handle* handle);

const char* sk_c_handle_errorType(const sk_c_handle* handle, char* buffer, int size);
const char* sk_c_handle_errorMessage(const sk_c_handle* handle, char* buffer, int size);

#if defined(__cplusplus)
}

#include <sk/util/String.h>

struct sk_c_handle 
{
  sk_c_handle();

  static char* copy(const std::string& s, char* buffer, int size);
  static void ensure_proper(const struct sk_c_handle* handle);

  bool error;
  sk::util::String errorType;
  sk::util::String errorMessage;
};

#endif

#endif /* _SK_C_HANDLE_H_ */

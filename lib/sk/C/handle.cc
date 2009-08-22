/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/C/handle.h>

#define SK_C_HANDLE_SIGNATURE "_SK_C_HANDLE_H_"

namespace {
  void abort_on_null_c_handle() {
    abort();
  }

  void abort_on_non_c_handle() {
    abort();
  }

  void abort_on_bad_copy_buffer() {
    abort();
  }

  sk::C::handle& make_c_handle(void* handle) {
    if(handle == 0) {
      abort_on_null_c_handle();
    }
    sk::C::handle* h = static_cast<sk::C::handle*>(handle);
    if(h->signature != SK_C_HANDLE_SIGNATURE) {
      abort_on_non_c_handle();
    }
    return *h;
  }
}

sk::C::handle::
handle()
  : error(false), signature(SK_C_HANDLE_SIGNATURE)
{
}

char* 
sk::C::handle::
copy(const std::string& s, char* buffer, int size)
{
  if(buffer == 0 || size <= 0) {
    abort_on_bad_copy_buffer();
  }
  strncpy(buffer, s.c_str(), size);
  buffer[size-1] = 0;

  return buffer;
}

extern "C"
int sk_c_handle_isError(void* handle) 
{
  sk::C::handle& h = make_c_handle(handle);
  return h.error == true ? 1 : 0;
}

extern "C"
int sk_c_handle_isGood(void* handle)
{
  sk::C::handle& h = make_c_handle(handle);
  return h.error == false ? 1 : 0;
}

extern "C"
const char* sk_c_handle_errorType(void* handle, char* buffer, int size)
{
  sk::C::handle& h = make_c_handle(handle);
  if(h.error == false) {
    return 0;
  }
  return sk::C::handle::copy(h.errorType, buffer, size);
}

extern "C"
const char* sk_c_handle_errorMessage(void* handle, char* buffer, int size)
{
  sk::C::handle& h = make_c_handle(handle);
  if(h.error == false) {
    return 0;
  }
  return sk::C::handle::copy(h.errorMessage, buffer, size);
}

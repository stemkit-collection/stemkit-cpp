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
#include <sk/util/Exception.h>
#include <sk/util/Class.h>
#include <string.h>

namespace {
  void abort_on_null_c_handle() {
    abort();
  }

  void abort_on_not_valid_c_handle() {
    abort();
  }

  void abort_on_bad_copy_buffer() {
    abort();
  }

  void abort_on_error_not_cleared() {
    abort();
  }

  void abort_on_object_not_available() {
    abort();
  }

  bool is_test_c_handle() {
    static bool flag = (getenv("SK_TEST_C_HANDLE") != 0);
    return flag;
  }

  const char* label = "*CREATED*";
}

namespace sk {
  namespace C {
    namespace debug {
      const char* error_message = 0;
      const char* error_type = 0;
    }
  }
}

sk_c_handle::
sk_c_handle()
  : _error(false)
{
  if(is_test_c_handle() == true) {
    _self = this;
    ::strncpy(_label, label, sizeof(_label));
  }
}

sk_c_handle::
~sk_c_handle()
{
  if(is_test_c_handle() == true) {
    _self = 0;
    ::strncpy(_label, "", sizeof(_label));
  }
}

bool
sk_c_handle::
isValid(const struct sk_c_handle* handle) const
{
  if(handle != this || _self != this) {
    return false;
  }
  if(::strncmp(label, _label, sizeof(_label)) != 0) {
    return false;
  }
  return true;
}

bool
sk_c_handle::
isError() const
{
  bool result = _error;
  _error = false;

  return result;
}

const sk::util::String& 
sk_c_handle::
errorType() const
{
  return _errorType;
}

const sk::util::String& 
sk_c_handle::
errorMessage() const
{
  return _errorMessage;
}

void
sk_c_handle::
ensure_not_null(const sk_c_handle* handle)
{
  if(handle == 0) {
    abort_on_null_c_handle();
  }
}

void
sk_c_handle::
ensure_valid(const sk_c_handle* handle)
{
  ensure_not_null(handle);
  if(is_test_c_handle() == true) {
    if(handle->isValid(handle) == false) {
      abort_on_not_valid_c_handle();
    }
  }
}

void
sk_c_handle::
ensure_proper(const sk_c_handle* handle)
{
  ensure_valid(handle);

  if(handle->isError() == true) {
    sk::C::debug::error_type = handle->errorType().getChars();
    sk::C::debug::error_message = handle->errorMessage().getChars();

    abort_on_error_not_cleared();
  }
  if(handle->hasObject() == false) {
    abort_on_object_not_available();
  }
}

void
sk_c_handle::
execute(const sk_c_handle::runnable& runnable) const
{
  try {
    runnable.run();
    _error = false;

    return;
  }
  catch(const sk::util::Exception& exception) {
    _errorType = exception.getClass().getName();
    _errorMessage = exception.getMessage();
  }
  catch(const std::exception& exception) {
    _errorType = "std::exception";
    _errorMessage = exception.what();
  }
  catch(...) {
    _errorType = "UNKNOWN";
    _errorMessage = "Unknown exception";
  }
  _error = true;
}

char* 
sk_c_handle::
copy(const std::string& s, char* buffer, int size)
{
  if(buffer == 0 || size <= 0) {
    abort_on_bad_copy_buffer();
  }
  strncpy(buffer, s.c_str(), size);
  buffer[size-1] = 0;

  return buffer;
}

char* 
sk_c_handle::
copy(const std::vector<char>& data, char* buffer, int size)
{
  if(buffer == 0 || size <= 0) {
    abort_on_bad_copy_buffer();
  }
  memcpy(buffer, &data.front(), std::min(data.size(), size_t(size)));
  return buffer;
}

extern "C"
int sk_c_handle_isError(const sk_c_handle* handle) 
{
  sk_c_handle::ensure_not_null(handle);
  return handle->isError() == true ? 1 : 0;
}

extern "C"
const char* sk_c_handle_errorType(const sk_c_handle* handle, char* buffer, int size)
{
  sk_c_handle::ensure_not_null(handle);
  return sk_c_handle::copy(handle->errorType(), buffer, size);
}

extern "C"
const char* sk_c_handle_errorMessage(const sk_c_handle* handle, char* buffer, int size)
{
  sk_c_handle::ensure_not_null(handle);
  return sk_c_handle::copy(handle->errorMessage(), buffer, size);
}

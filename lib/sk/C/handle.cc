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

namespace {
  void abort_on_null_c_handle() {
    abort();
  }

  void abort_on_bad_copy_buffer() {
    abort();
  }
}

sk_c_handle::
sk_c_handle()
  : _error(false)
{
}

bool
sk_c_handle::
isError() const
{
  return _error;
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
ensure_proper(const sk_c_handle* handle)
{
  if(handle == 0) {
    abort_on_null_c_handle();
  }
}

void
sk_c_handle::
execute(const sk_c_handle::Runnable& runnable) const
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

extern "C"
int sk_c_handle_isError(const sk_c_handle* handle) 
{
  sk_c_handle::ensure_proper(handle);
  return handle->isError() == true ? 1 : 0;
}

extern "C"
int sk_c_handle_isGood(const sk_c_handle* handle)
{
  sk_c_handle::ensure_proper(handle);
  return handle->isError() == false ? 1 : 0;
}

extern "C"
const char* sk_c_handle_errorType(const sk_c_handle* handle, char* buffer, int size)
{
  sk_c_handle::ensure_proper(handle);
  if(handle->isError() == false) {
    return 0;
  }
  return sk_c_handle::copy(handle->errorType(), buffer, size);
}

extern "C"
const char* sk_c_handle_errorMessage(const sk_c_handle* handle, char* buffer, int size)
{
  sk_c_handle::ensure_proper(handle);
  if(handle->isError() == false) {
    return 0;
  }
  return sk_c_handle::copy(handle->errorMessage(), buffer, size);
}

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/rt/Lock.h>

namespace {
  struct FunctionInvocator {
    FunctionInvocator(sk::rt::Lock::function_t& function)
      : _function(function) {}

    void invoke() {
      (_function)();
    }
    sk::rt::Lock::function_t& _function;
  };
}

template<> 
void 
sk::rt::Lock::
synchronize<sk::rt::Lock::function_t>(sk::rt::Lock::function_t& function)
{
  FunctionInvocator invocator(function);
  synchronize(invocator, &FunctionInvocator::invoke);
}


/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/rt/SystemException.h>
#include "foreach_environment_item.h"
#include <windows.h>

void sk::rt::foreach_environment_item(const sk::util::Processor<const sk::util::String>& processor) {
  LPTCH environ = GetEnvironmentStrings();

  if(environ == 0) {
    throw sk::rt::SystemException("GetEnvironmentStrings");
  }
  try {
    LPTCH item = environ;
    while(*item != 0) {
      processor.process(item);
      item += strlen(item) + 1;
    }
  }
  catch(...) {
    FreeEnvironmentStrings(environ);
    throw;
  }
  if(FreeEnvironmentStrings(environ) == FALSE) {
    throw sk::rt::SystemException("FreeEnvironmentStrings");
  }
}

/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "../foreach_environment_item.h"
#include <unistd.h>

void sk::rt::foreach_environment_item(const sk::util::Processor<const sk::util::String>& processor) {
  for(char** iterator = environ; *iterator ;++iterator) {
    processor.process(*iterator);
  }
}

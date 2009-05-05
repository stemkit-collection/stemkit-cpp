/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_FOREACH_ENVIRONMENT_ITEM_H_
#define _SK_RT_FOREACH_ENVIRONMENT_ITEM_H_

#include <sk/util/String.h>
#include <sk/util/Processor.h>

namespace sk {
  namespace rt {
    void foreach_environment_item(const sk::util::Processor<const sk::util::String>& processor);
  }
}

#endif /* _SK_RT_FOREACH_ENVIRONMENT_ITEM_H_ */

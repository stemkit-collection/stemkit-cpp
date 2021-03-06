/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_CONFIGURABLESOCKET_H_
#define _SK_NET_CONFIGURABLESOCKET_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class ConfigurableSocket
      : public virtual sk::util::Object
    {
      public:
        virtual void setReuseAddress(bool state) = 0;
    };
  }
}

#endif /* _SK_NET_CONFIGURABLESOCKET_H_ */

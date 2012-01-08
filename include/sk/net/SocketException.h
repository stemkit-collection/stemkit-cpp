/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_SOCKETEXCEPTION_H_
#define _SK_NET_SOCKETEXCEPTION_H_

#include <sk/rt/SystemException.h>

namespace sk {
  namespace net {
    class SocketException
      : public sk::rt::SystemException
    {
      public:
        SocketException(const sk::util::String& message);
        SocketException(const sk::util::String& message, const sk::util::Strings& details);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_NET_SOCKETEXCEPTION_H_ */

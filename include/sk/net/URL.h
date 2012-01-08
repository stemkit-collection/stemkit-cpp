/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_URL_H_
#define _SK_NET_URL_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class URL
      : public virtual sk::util::Object
    {
      public:
        URL();
        virtual ~URL();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        URL(const URL& other);
        URL& operator = (const URL& other);
    };
  }
}

#endif /* _SK_NET_URL_H_ */

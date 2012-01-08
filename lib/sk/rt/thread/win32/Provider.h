/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_WIN32_PROVIDER_H_
#define _SK_RT_THREAD_WIN32_PROVIDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace win32 {
        class Provider
          : public virtual sk::util::Object
        {
          public:
            virtual void installGeneric(sk::rt::thread::Generic& handle) const = 0;
            virtual void clearGeneric() const = 0;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_WIN32_PROVIDER_H_ */

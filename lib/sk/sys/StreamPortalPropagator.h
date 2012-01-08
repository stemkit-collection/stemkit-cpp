/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_SYS_STREAMPORTALPROPAGATOR_H_
#define _SK_SYS_STREAMPORTALPROPAGATOR_H_

#include <sk/util/String.h>
#include <sk/util/Processor.h>

namespace sk {
  namespace sys {
    class StreamPortalPropagator
      : public virtual sk::util::Processor<const sk::util::String>
    {
      public:
        int propagate(int fd) const;

        // sk::util::Processor implementation.
        void process(const sk::util::String& descriptor) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        StreamPortalPropagator& operator = (const StreamPortalPropagator& other);
    };
  }
}

#endif /* _SK_SYS_STREAMPORTALPROPAGATOR_H_ */

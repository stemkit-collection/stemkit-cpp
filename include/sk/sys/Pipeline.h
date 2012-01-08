/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_PIPELINE_
#define _SK_SYS_PIPELINE_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class Pipeline
      : public virtual sk::util::Object
    {
      public:
        Pipeline();
        virtual ~Pipeline();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Pipeline(const Pipeline& other);
        Pipeline& operator = (const Pipeline& other);
    };
  }
}

#endif /* _SK_SYS_PIPELINE_ */

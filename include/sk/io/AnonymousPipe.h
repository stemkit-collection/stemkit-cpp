/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ANONYMOUSPIPE_
#define _SK_IO_ANONYMOUSPIPE_

#include <sk/io/AbstractFileDescriptorPipe.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace io {
    class AnonymousPipe
      : public sk::io::AbstractFileDescriptorPipe
    {
      public:
        AnonymousPipe();
        virtual ~AnonymousPipe();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        static void ignoreSignals();
        static void resetSignals();

      private:
        AnonymousPipe(const AnonymousPipe& other);
        AnonymousPipe& operator = (const AnonymousPipe& other);

        const sk::rt::Scope _scope;
    };
  }
}

#endif /* _SK_IO_ANONYMOUSPIPE_ */

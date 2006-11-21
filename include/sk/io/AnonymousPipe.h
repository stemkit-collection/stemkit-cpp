/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ANONYMOUSPIPE_
#define _SK_IO_ANONYMOUSPIPE_

#include <sk/io/AbstractPipe.h>

namespace sk {
  namespace io {
    class AnonymousPipe
      : public sk::io::AbstractPipe
    {
      public:
        AnonymousPipe();
        virtual ~AnonymousPipe();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        AnonymousPipe(const AnonymousPipe& other);
        AnonymousPipe& operator = (const AnonymousPipe& other);
    };
  }
}

#endif /* _SK_IO_ANONYMOUSPIPE_ */

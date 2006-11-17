/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_STANDARDSTREAMPROVIDER_
#define _SK_SYS_STANDARDSTREAMPROVIDER_

#include <sk/util/Object.h>
#include <sk/io/Pipe.h>

namespace sk {
  namespace sys {
    class StandardStreamProvider
      : public virtual sk::util::Object 
    {
      public:
        virtual sk::io::Pipe& getStdin() const = 0;
        virtual sk::io::Pipe& getStdout() const = 0;
        virtual sk::io::Pipe& getStderr() const = 0;
    };
  }
}

#endif /* _SK_SYS_STANDARDSTREAMPROVIDER_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_STANDARDSTREAMPROVIDER_
#define _SK_IO_STANDARDSTREAMPROVIDER_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Pipe;

    class StandardStreamProvider
      : public virtual sk::util::Object 
    {
      public:
        virtual Pipe& getStdin() const = 0;
        virtual Pipe& getStdout() const = 0;
        virtual Pipe& getStderr() const = 0;
    };
  }
}

#endif /* _SK_IO_STANDARDSTREAMPROVIDER_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ABSTRACTOUTPUTSTREAM_
#define _SK_IO_ABSTRACTOUTPUTSTREAM_

#include <sk/io/OutputStream.h>

namespace sk {
  namespace io {
    class AbstractOutputStream
      : public virtual sk::io::OutputStream
    {
      public:
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_IO_ABSTRACTOUTPUTSTREAM_ */

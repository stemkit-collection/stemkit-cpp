/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_EOFEXCEPTION_
#define _SK_IO_EOFEXCEPTION_

#include <sk/io/IOException.h>

namespace sk {
  namespace io {
    class EOFException
      : public sk::io::IOException
    {
      public:
        EOFException();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_IO_EOFEXCEPTION_ */

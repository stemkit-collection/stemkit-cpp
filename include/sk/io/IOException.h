/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_IOEXCEPTION_
#define _SK_IO_IOEXCEPTION_

#include <sk/util/Exception.h>

namespace sk {
  namespace io {
    class IOException
      : public sk::util::Exception
    {
      public:
        IOException(const sk::util::String& message);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_IO_IOEXCEPTION_ */

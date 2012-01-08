/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_CLOSEDCHANNELEXCEPTION_
#define _SK_IO_CLOSEDCHANNELEXCEPTION_

#include <sk/io/IOException.h>

namespace sk {
  namespace io {
    class ClosedChannelException
      : public sk::io::IOException
    {
      public:
        ClosedChannelException();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_IO_CLOSEDCHANNELEXCEPTION_ */

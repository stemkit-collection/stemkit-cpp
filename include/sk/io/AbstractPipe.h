/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ABSTRACTPIPE_
#define _SK_IO_ABSTRACTPIPE_

#include <sk/io/Pipe.h>

namespace sk {
  namespace io {
    class AbstractPipe
      : public virtual sk::io::Pipe
    {
      public:
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::Pipe implementation.
        void close();
        void closeInput();
        void closeOutput();
        InputStream& inputStream() const;
        OutputStream& outputStream() const;
    };
  }
}

#endif /* _SK_IO_ABSTRACTPIPE_ */

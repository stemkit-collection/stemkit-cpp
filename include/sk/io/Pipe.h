/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PIPE_
#define _SK_IO_PIPE_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class InputStream;
    class OutputStream;

    class Pipe
      : public virtual sk::util::Object 
    {
      public:
        virtual void close() = 0;
        virtual void closeInput() = 0;
        virtual void closeOutput() = 0;

        virtual InputStream& inputStream() const = 0;
        virtual OutputStream& outputStream() const = 0;
    };
  }
}

#endif /* _SK_IO_PIPE_ */

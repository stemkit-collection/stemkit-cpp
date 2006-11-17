/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTY_
#define _SK_IO_PTY_

#include <sk/util/Object.h>
#include <sk/io/Tty.h>
#include <sk/io/Pipe.h>

namespace sk {
  namespace io {
    class Pty
      : public sk::io::Tty,
        public virtual sk::io::Pipe
    {
      public:
        Pty();
        virtual ~Pty();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::Pipe implementation.
        void close();
        void closeInput();
        void closeOutput();
        FileDescriptorInputStream& inputStream() const;
        FileDescriptorOutputStream& outputStream() const;
        
      private:
        Pty(const Pty& other);
        Pty& operator = (const Pty& other);
    };
  }
}

#endif /* _SK_IO_PTY_ */

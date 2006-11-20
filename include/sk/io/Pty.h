/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTY_
#define _SK_IO_PTY_

#include <sk/util/Holder.hxx>
#include <sk/io/DelegatingTty.h>
#include <sk/io/Pipe.h>

namespace sk {
  namespace io {
    class PtyImpl;

    class Pty
      : public sk::io::DelegatingTty,
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

        // sk::io::DelegatingTty implementation.
        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;

        sk::util::Holder<PtyImpl> _implHolder;
    };
  }
}

#endif /* _SK_IO_PTY_ */

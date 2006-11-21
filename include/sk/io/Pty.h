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
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

namespace sk {
  namespace io {
    class PtyImpl;

    class Pty
      : public sk::io::DelegatingTty
    {
      public:
        Pty();
        virtual ~Pty();

        void close();
        const sk::util::String getName() const;
        sk::io::Pipe& getMasterSlavePipe();
        sk::io::Pipe& getSlaveMasterPipe();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Pty(const Pty& other);
        Pty& operator = (const Pty& other);

        // sk::io::DelegatingTty implementation.
        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;

        sk::util::Holder<PtyImpl> _implHolder;
        sk::util::Holder<sk::io::Pipe> _masterSlavePipeHolder;
        sk::util::Holder<sk::io::Pipe> _slaveMasterPipeHolder;
    };
  }
}

#endif /* _SK_IO_PTY_ */

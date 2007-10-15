/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTY_
#define _SK_IO_PTY_

#include <sk/util/Holder.hxx>
#include <sk/util/String.h>
#include <sk/io/DelegatingTty.h>
#include <sk/io/Pipe.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

namespace sk {
  namespace io {
    class TtyFileDescriptor;

    class Pty
      : public sk::io::DelegatingTty
    {
      public:
        Pty();
        virtual ~Pty();

        const sk::util::String getName() const;

        void close();
        void closeTty();

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

        sk::util::String _name;
        sk::util::Holder<sk::io::TtyFileDescriptor> _ttyHolder;
        sk::util::Holder<sk::io::Pipe> _slaveMasterPipeHolder;
        sk::util::Holder<sk::io::Pipe> _masterSlavePipeHolder;
    };
  }
}

#endif /* _SK_IO_PTY_ */
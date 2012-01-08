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
#include <sk/io/FileDescriptorPipe.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/rt/Scope.h>

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

        sk::io::FileDescriptorPipe& getMasterSlavePipe();
        sk::io::FileDescriptorPipe& getSlaveMasterPipe();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Pty(const Pty& other);
        Pty& operator = (const Pty& other);

        // sk::io::DelegatingTty implementation.
        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;

        const sk::rt::Scope _scope;
        sk::util::String _name;
        sk::util::Holder<sk::io::TtyFileDescriptor> _ttyHolder;
        sk::util::Holder<sk::io::FileDescriptorPipe> _slaveMasterPipeHolder;
        sk::util::Holder<sk::io::FileDescriptorPipe> _masterSlavePipeHolder;
    };
  }
}

#endif /* _SK_IO_PTY_ */

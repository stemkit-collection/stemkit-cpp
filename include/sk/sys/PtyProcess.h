/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_PTYPROCESS_
#define _SK_SYS_PTYPROCESS_

#include <sk/util/Holder.hxx>
#include <sk/sys/Process.h>
#include <sk/sys/DelegatingExecutable.h>
#include <sk/rt/Scope.h>

#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>
#include <sk/io/Pty.h>

namespace sk {
  namespace sys {
    class PtyProcess
      : public virtual sk::sys::DelegatingExecutable
    {
      public:
        PtyProcess(const sk::util::StringArray& cmdline);
        virtual ~PtyProcess();

        sk::io::Pty& getPty();

        sk::io::InputStream& inputStream() const;
        sk::io::InputStream& inputErrorStream() const;
        sk::io::OutputStream& outputStream() const;

        const sk::util::StringArray& errors() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        PtyProcess(const PtyProcess& other);
        PtyProcess& operator = (const PtyProcess& other);

        // sk::sys::DelegatingExecutable implementation.
        sk::sys::Executable& getExecutable();
        const sk::sys::Executable& getExecutable() const;
        
        struct Listener;

        const sk::rt::Scope _scope;
        sk::util::Holder<Listener> _listenerHolder;
        sk::sys::Process _process;
    };
  }
}

#endif /* _SK_SYS_PTYPROCESS_ */

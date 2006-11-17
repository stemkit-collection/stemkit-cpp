/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_PROCESS_
#define _SK_SYS_PROCESS_

#include <sk/util/Object.h>
#include <sk/util/StringArray.h>
#include <sk/util/Holder.hxx>
#include <sk/sys/StandardStreamProvider.h>
#include <sk/io/FileDescriptor.h>

namespace sk {
  namespace sys {
    class Process
      : public virtual sk::sys::StandardStreamProvider
    {
      public:
        Process(const sk::sys::StandardStreamProvider& streamProvider, const sk::util::StringArray& cmdline);
        Process(const sk::util::StringArray& cmdline);
        virtual ~Process();
        
        void stop();
        void join();

        bool isSuccess() const;
        bool isExited() const;
        bool isKilled() const;
        bool isAlive() const;
        int exitStatus() const;
        int signal() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::StandardStreamProvider implementation.
        sk::io::Pipe& getStdin() const;
        sk::io::Pipe& getStdout() const;
        sk::io::Pipe& getStderr() const;

      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        void start(const sk::util::StringArray& cmdline);
        void redirect(int from, const sk::io::FileDescriptor& to);
        bool signalUnlessTerminates(int timeout, int signal);
        void assertNotAlive() const;
        void processChild(const sk::util::StringArray& cmdline);

        sk::util::Holder<const sk::sys::StandardStreamProvider> _streamProviderHolder;
        sk::util::Holder<sk::sys::StandardStreamProvider> _ownStreamProviderHolder;
        sk::util::StringArray _errors;
        int _pid;
        int _status;
    };
  }
}

#endif /* _SK_SYS_PROCESS_ */

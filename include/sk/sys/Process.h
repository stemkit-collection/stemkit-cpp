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
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/sys/Executable.h>
#include <sk/sys/ProcessListener.h>

namespace sk {
  namespace sys {
    class Process
      : public virtual sk::sys::Executable,
        public virtual sk::sys::ProcessListener
    {
      public:
        Process(sk::io::FileDescriptorInputStream& inputStream, const sk::util::StringArray& cmdline, ProcessListener& listener);
        Process(sk::io::FileDescriptorInputStream& inputStream, const sk::util::StringArray& cmdline);
        Process(const sk::util::StringArray& cmdline, ProcessListener& listener);
        Process(const sk::util::StringArray& cmdline);
        virtual ~Process();
        
        // sk::sys::Executable implementation.
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

        // sk::sys::ProcessListener implementation.
        void processStarting();
        int processStopping();
        void processJoining();

      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        void start(const sk::util::StringArray& cmdline);
        void redirect(int from, const sk::io::FileDescriptor& to);
        bool signalUnlessTerminates(int timeout, int signal);
        void assertNotAlive() const;
        void processChild(const sk::util::StringArray& cmdline);

        sk::util::Holder<sk::io::FileDescriptorInputStream> _inputStreamHolder;
        sk::sys::ProcessListener& _listener;
        int _pid;
        int _status;
    };
  }
}

#endif /* _SK_SYS_PROCESS_ */

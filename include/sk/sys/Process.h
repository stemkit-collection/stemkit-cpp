/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
#include <sk/sys/AbstractProcessListener.h>
#include <sk/rt/Scope.h>
#include <sk/rt/Mutex.h>

namespace sk {
  namespace sys {
    class StreamPortal;

    class Process
      : public virtual sk::sys::Executable,
        public sk::sys::AbstractProcessListener
    {
      public:
        Process(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline, ProcessListener& listener);
        Process(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline);
        Process(sk::io::InputStream& inputStream, ProcessListener& listener);
        Process(const sk::util::StringArray& cmdline, ProcessListener& listener);
        Process(const sk::util::StringArray& cmdline);
        Process(ProcessListener& listener);
        virtual ~Process();

        static void setup();
        static void reset();

        static sk::sys::StreamPortal& streamPortal();

        // sk::sys::Executable implementation.
        void stop();
        void kill();
        void join();
        void detach();
        bool isSuccess() const;
        bool isExited() const;
        bool isKilled() const;
        bool isAlive() const;
        int exitStatus() const;
        int signal() const;
        int getPid() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::sys::ProcessListener implementation.
        void processStarting(sk::io::Stream& umbilical);
        int processStopping();
        void processJoining();

      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        struct Implementation;
        Implementation& process() const;

        void start(sk::io::InputStream& inputStream, const sk::util::StringArray& cmdline);
        void start(const sk::util::StringArray& cmdline);
        void ensureNotRunning() const;

        const sk::rt::Scope _scope;
        sk::sys::ProcessListener& _listener;
        sk::rt::Mutex _mutex;

        volatile int _pid;
        volatile bool _detached;
        volatile bool _running;

        sk::util::Holder<Implementation> _implementationHolder;
    };
  }
}

#endif /* _SK_SYS_PROCESS_ */

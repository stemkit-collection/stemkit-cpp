/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PROCESS_
#define _SK_IO_PROCESS_

#include <sk/util/Object.h>
#include <sk/io/ProcessListener.h>

namespace sk {
  namespace io {
    class Pipe;

    class Process
      : public virtual sk::io::ProcessListener
    {
      public:
        Process(sk::io::Pipe& pipe);
        Process(sk::io::Pipe& pipe, sk::io::ProcessListener& listener);
        virtual ~Process();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::ProcessListener implementation.
        void started(io::Process& process);
        void finished(io::Process& process);
        void exec(const sk::util::String& command, const std::vector<char*>& args);
        
      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        sk::io::Pipe& _pipe;
        sk::io::ProcessListener& _listener;
    };
  }
}

#endif /* _SK_IO_PROCESS_ */

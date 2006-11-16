/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PROCESS_
#define _SK_IO_PROCESS_

#include <sk/util/Object.h>
#include <sk/util/StringArray.h>
#include <sk/io/StandardStreamProvider.h>

namespace sk {
  namespace io {
    class Pipe;

    class Process
      : public virtual sk::io::StandardStreamProvider
    {
      public:
        Process(const sk::io::StandardStreamProvider& streamProvider, const sk::util::StringArray& cmdline);
        Process(const sk::util::StringArray& cmdline);
        virtual ~Process();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::StandardStreamProvider implementation.
        sk::io::Pipe& getStdin() const;
        sk::io::Pipe& getStdout() const;
        sk::io::Pipe& getStderr() const;
        
      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        void exec(const sk::util::String& command, const std::vector<char*>& args);
    };
  }
}

#endif /* _SK_IO_PROCESS_ */

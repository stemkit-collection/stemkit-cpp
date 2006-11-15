/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PROCESSLISTENER_
#define _SK_IO_PROCESSLISTENER_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

namespace sk {
  namespace io {
    class Process;

    class ProcessListener
      : public virtual sk::util::Object 
    {
      public:
        virtual void started(io::Process& process) = 0;
        virtual void finished(io::Process& process) = 0;
        virtual void exec(const sk::util::String& command, const std::vector<char*>& args) = 0;
    };
  }
}

#endif /* _SK_IO_PROCESSLISTENER_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PROCESS_
#define _SK_IO_PROCESS_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Pipe;

    class Process
      : public virtual sk::util::Object 
    {
      public:
        Process(sk::io::Pipe& pipe);
        virtual ~Process();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Process(const Process& other);
        Process& operator = (const Process& other);

        sk::io::Pipe& _pipe;
    };
  }
}

#endif /* _SK_IO_PROCESS_ */

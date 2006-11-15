/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PIPE_
#define _SK_IO_PIPE_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Pipe
      : public virtual sk::util::Object 
    {
      public:
        Pipe();
        virtual ~Pipe();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Pipe(const Pipe& other);
        Pipe& operator = (const Pipe& other);
    };
  }
}

#endif /* _SK_IO_PIPE_ */

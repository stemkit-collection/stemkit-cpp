/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TTY_
#define _SK_IO_TTY_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Tty
      : public virtual sk::util::Object 
    {
      public:
        Tty();
        virtual ~Tty();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Tty(const Tty& other);
        Tty& operator = (const Tty& other);
    };
  }
}

#endif /* _SK_IO_TTY_ */

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
        virtual void setLines(int lines) = 0;
        virtual void setColumns(int columns) = 0;
    };
  }
}

#endif /* _SK_IO_TTY_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DELEGATINGTTY_
#define _SK_IO_DELEGATINGTTY_

#include <sk/io/Tty.h>

namespace sk {
  namespace io {
    class DelegatingTty
      : public virtual sk::io::Tty 
    {
      public:
        DelegatingTty();
        virtual ~DelegatingTty();

        void setLines(int lines);
        void setColumns(int columns);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      protected:
        virtual sk::io::Tty& getTty() = 0;
        virtual const sk::io::Tty& getTty() const = 0;

    };
  }
}

#endif /* _SK_IO_DELEGATINGTTY_ */

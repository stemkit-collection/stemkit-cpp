/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTYIMPL_
#define _SK_IO_PTYIMPL_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace io {
    class Tty;

    class PtyImpl
      : public virtual sk::util::Object 
    {
      public:
        PtyImpl();
        virtual ~PtyImpl();

        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        PtyImpl(const PtyImpl& other);
        PtyImpl& operator = (const PtyImpl& other);

        sk::util::Holder<sk::io::Tty> _ttyHolder;
    };
  }
}

#endif /* _SK_IO_PTYIMPL_ */

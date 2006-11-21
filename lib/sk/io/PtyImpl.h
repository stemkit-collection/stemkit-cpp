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
#include <sk/io/File.h>

#include "PtySpecifics.h"

namespace sk {
  namespace io {
    class TtyDevice;

    class PtyImpl
      : public sk::io::PtySpecifics
    {
      public:
        PtyImpl();
        virtual ~PtyImpl();

        sk::io::File& getMaster();
        sk::io::TtyDevice& getSlave();

        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::PtySpecifics implementation.
        int makeSlave(const sk::util::String& name);

      private:
        PtyImpl(const PtyImpl& other);
        PtyImpl& operator = (const PtyImpl& other);

        sk::util::Holder<sk::io::TtyDevice> _deviceHolder;
        sk::io::File _master;
    };
  }
}

#endif /* _SK_IO_PTYIMPL_ */

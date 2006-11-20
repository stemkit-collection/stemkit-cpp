/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TTYDEVICE_
#define _SK_IO_TTYDEVICE_

#include <sk/io/Tty.h>
#include <sk/io/File.h>

namespace sk {
  namespace io {
    class TtyDevice
      : public sk::io::File,
        public virtual sk::io::Tty
    {
      public:
        TtyDevice(const sk::util::String& name);
        virtual ~TtyDevice();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        TtyDevice(const TtyDevice& other);
        TtyDevice& operator = (const TtyDevice& other);
    };
  }
}

#endif /* _SK_IO_TTYDEVICE_ */

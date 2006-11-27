/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TTYDEVICE_
#define _SK_IO_TTYDEVICE_

#include <sk/util/Holder.hxx>
#include <sk/io/DelegatingTty.h>
#include <sk/io/TtyFileDescriptor.h>
#include <sk/io/File.h>

namespace sk {
  namespace io {
    class TtyDevice
      : public sk::io::File,
        public virtual sk::io::DelegatingTty
    {
      public:
        TtyDevice(const sk::util::String& name);
        virtual ~TtyDevice();

        // sk::io::File reimplementation.
        void close();
        sk::io::TtyFileDescriptor& getFileDescriptor() const;

        // sk::io::DelegatingTty implementation.
        sk::io::Tty& getTty();
        const sk::io::Tty& getTty() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        TtyDevice(const TtyDevice& other);
        TtyDevice& operator = (const TtyDevice& other);

        sk::util::Holder<sk::io::TtyFileDescriptor> _descriptorHolder;
    };
  }
}

#endif /* _SK_IO_TTYDEVICE_ */

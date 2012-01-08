/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TTYFILEDESCRIPTOR_
#define _SK_IO_TTYFILEDESCRIPTOR_

#include <sk/io/FileDescriptor.h>
#include <sk/io/Tty.h>

namespace sk {
  namespace io {
    class TtyFileDescriptor
      : public sk::io::FileDescriptor,
        public virtual sk::io::Tty
    {
      public:
        TtyFileDescriptor(int fd);
        TtyFileDescriptor(const sk::io::FileDescriptor& descriptor);
        // Enabling copy constructor, the default one will do for now.
        // TtyFileDescriptor(const TtyFileDescriptor& other);
        virtual ~TtyFileDescriptor();

        // sk::io::Tty implementation.
        void setLines(int lines);
        void setColumns(int columns);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        TtyFileDescriptor& operator = (const TtyFileDescriptor& other);

        void ensureTty();
    };
  }
}

#endif /* _SK_IO_TTYFILEDESCRIPTOR_ */

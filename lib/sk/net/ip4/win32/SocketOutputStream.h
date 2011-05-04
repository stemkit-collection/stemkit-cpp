/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_NET_WIN32_SOCKETOUTPUTSTREAM_
#define _SK_NET_WIN32_SOCKETOUTPUTSTREAM_

#include <sk/io/AbstractOutputStream.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/FileDescriptorProvider.h>

namespace sk {
  namespace net {
    namespace win32 {
      class SocketOutputStream
        : public sk::io::AbstractOutputStream,
          public virtual sk::io::FileDescriptorProvider
      {
        public:
          SocketOutputStream(int fd);
          SocketOutputStream(const sk::io::FileDescriptor& descriptor);
          SocketOutputStream(const SocketOutputStream& other);
          virtual ~SocketOutputStream();

          // sk::io::FileDescriptorProvider implementation.
          const sk::io::FileDescriptor& getFileDescriptor() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          sk::util::Object* clone() const;
          const sk::util::String inspect() const;

          // sk::io::OutputStream implementation.
          int write(const char* buffer, int offset, int length);
          using AbstractOutputStream::write;
          void close();
          void inheritable(bool state);
          
        private:
          SocketOutputStream& operator = (const SocketOutputStream& other);

          sk::io::FileDescriptor _descriptor;
      };
    }
  }
}

#endif /* _SK_NET_WIN32_SOCKETOUTPUTSTREAM_ */

/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_NET_WIN32_SOCKETINPUTSTREAM_
#define _SK_NET_WIN32_SOCKETINPUTSTREAM_

#include <sk/io/AbstractInputStream.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/FileDescriptorProvider.h>

namespace sk {
  namespace net {
    namespace win32 {
      class SocketInputStream
        : public sk::io::AbstractInputStream, 
          public virtual sk::io::FileDescriptorProvider
      {
        public:
          SocketInputStream(int fd);
          SocketInputStream(const sk::io::FileDescriptor& descriptor);
          SocketInputStream(const SocketInputStream& other);
          virtual ~SocketInputStream();

          // sk::io::FileDescriptorProvider implementation.
          const sk::io::FileDescriptor& getFileDescriptor() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          sk::util::Object* clone() const;
          const sk::util::String inspect() const;

          // sk::io::InputStream implementation.
          int read(char* buffer, int offset, int length);
          using sk::io::AbstractInputStream::read;
          void close();
          void inheritable(bool state);
          
        private:
          SocketInputStream& operator = (const SocketInputStream& other);

          sk::io::FileDescriptor _descriptor;
      };
    }
  }
}

#endif /* _SK_NET_WIN32_SOCKETINPUTSTREAM_ */

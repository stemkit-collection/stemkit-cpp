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

#include <winsock2.h>
#include <ws2tcpip.h>

namespace sk {
  namespace net {
    namespace win32 {
      class SocketOutputStream
        : public sk::io::AbstractOutputStream
      {
        public:
          SocketOutputStream(const SOCKET socket);
          SocketOutputStream(const SocketOutputStream& other);
          virtual ~SocketOutputStream();

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

          SOCKET _socket;
      };
    }
  }
}

#endif /* _SK_NET_WIN32_SOCKETOUTPUTSTREAM_ */

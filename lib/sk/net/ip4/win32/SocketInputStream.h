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

#include <winsock2.h>
#include <ws2tcpip.h>

namespace sk {
  namespace net {
    namespace win32 {
      class SocketInputStream
        : public sk::io::AbstractInputStream
      {
        public:
          SocketInputStream(const SOCKET socket);
          SocketInputStream(const SocketInputStream& other);
          virtual ~SocketInputStream();

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

          SOCKET _socket;
      };
    }
  }
}

#endif /* _SK_NET_WIN32_SOCKETINPUTSTREAM_ */

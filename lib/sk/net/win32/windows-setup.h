/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_NET_WIN32_WINDOWS_SETUP_H_
#define _SK_NET_WIN32_WINDOWS_SETUP_H_

#include <winsock2.h>
#include <ws2tcpip.h>

namespace {
  class Initiator {
    public:
      Initiator() {
        WORD version = MAKEWORD(2, 2);
        WSADATA data;

        const int status = WSAStartup(version, &data);
        if(status != 0) {
          std::cerr << "ERROR: WSAStartup() failed with error " << status << std::endl;
          exit(2);
        }
      }

      ~Initiator() {
        WSACleanup();
      }
  };

  Initiator initiator;
}

#endif /* _SK_NET_WIN32_WINDOWS_SETUP_H_ */

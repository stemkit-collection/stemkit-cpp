/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/util/IllegalArgumentException.h>
#include <sk/rt/SystemException.h>
#include <sk/util/Integer.h>
#include <sk/util/Container.h>
#include <sk/rt/Scope.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/AbstractProcessListener.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

int start_listener(int port);
int accept_connection(int sock);
void process_request(int sock);

int main(int argc, const char* argv[])
{
  sk::rt::Scope scope("main");
  if(argc != 2) {
    throw sk::util::IllegalArgumentException("main()");
  }
  int sock = start_listener(sk::util::Integer::parseInt(argv[1]));

  while(true) {
    process_request(accept_connection(sock));
  }
}

int start_listener(int port) {
  sk::rt::Scope scope(__FUNCTION__);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    throw sk::rt::SystemException("socket");
  }

  int opt_on = 1;
  if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt_on), sizeof(opt_on)) < 0) {
    throw sk::rt::SystemException("setsockopt");
  }

  sockaddr_in sock_addr = { 0 };
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(port);
  sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(sock, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr) ) < 0) {
    throw sk::rt::SystemException("bind");
  }

  if(listen(sock, 1) !=0) {
    throw sk::rt::SystemException("listen");
  }
  scope.info() << "Started listner on port " << port;
  return sock;
}

int accept_connection(int sock) {
  struct sockaddr_in sock_addr;
  socklen_t length = sizeof(sock_addr);

  int fd = accept(sock, reinterpret_cast<sockaddr*>(&sock_addr), &length);
  if(fd >= 0) {
    return fd;
  }
  throw sk::rt::SystemException("accept");
}

namespace {
  struct Configurator : public sk::sys::AbstractProcessListener {
    Configurator(const sk::io::Stream& stream)
      : _stream(stream) {}

    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      configurator.addStream(_stream);
    }
    const sk::io::Stream& _stream;
  };
}

void process_request(int fd) {
  sk::io::FileDescriptorOutputStream stream(fd);
  Configurator configurator(stream);
  sk::sys::Process process(sk::util::StringArray("tcp-echo-client"), configurator);

  // stream.close();
  process.join();
}

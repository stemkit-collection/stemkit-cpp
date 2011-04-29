/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/net/ServerSocket.h>

int main(int argc, const char* const argv[])
{
  sk::net::ServerSocket server(8787);
  std::cerr << "Listening on " << server << std::endl;
  sk::net::Socket socket = server.accept();

  std::cerr << "Got connection from " << socket.getRemoteAddress() << ", port " << socket.getRemotePort() << std::endl;

  return 0;
}

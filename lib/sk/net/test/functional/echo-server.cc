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
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>

#include <sk/io/EOFException.h>

int main(int argc, const char* const argv[])
{
  sk::net::ServerSocket server(8787);
  std::cerr << "Listening on " << server.endpoint() << std::endl;
  
  sk::net::Socket socket = server.accept();
  std::cerr << "Got connection from " << socket.endpoint() << std::endl;

  sk::io::DataInputStream inputStream(socket.inputStream());
  sk::io::DataOutputStream outputStream(socket.outputStream());

  try { 
    while(true) {
      const sk::util::String line = inputStream.readLine();

      std::cerr << "L: " << line.inspect() << std::endl;
      outputStream.writeChars(line.toUpperCase());
    }
  }
  catch(const sk::io::EOFException& exception) {}
  return 0;
}

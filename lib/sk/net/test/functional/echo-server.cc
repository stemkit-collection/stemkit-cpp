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

#include <sk/util/Integer.h>
#include <sk/net/ServerSocket.h>
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>

#include <sk/io/EOFException.h>

int main(int argc, const char* const argv[])
{
  sk::net::ServerSocket server(sk::util::Integer::parseInt(argv[1]));
  server.setReuseAddress(true);

  std::cerr << "Listening on " << server.endpoint() << " (" << server.bind().localEndpoint() << ")" << std::endl;
  
  try {
    while(true) {
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
      catch(const sk::io::EOFException& exception) {
        std::cerr << "Disconnected from " << socket.endpoint() << std::endl;
      }
    }
  }
  catch(const std::exception& exception) {
    std::cerr << "EX: " << exception.what() << std::endl;
  }
  catch(...) {
    std::cerr << "EX: UNKNOWN" << std::endl;
  }
  return 0;
}

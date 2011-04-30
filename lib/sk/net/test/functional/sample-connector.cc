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

#include <sk/util/exception/Tracer.h>
#include <sk/rt/StackTracerFactory.h>

#include <sk/net/Socket.h>
#include <sk/net/ip4/InetAddress.h>

#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/io/EOFException.h>

int main(int argc, const char* const argv[])
{
  // sk::rt::StackTracerFactory factory;
  // sk::util::exception::Tracer::setProducerFactory(factory);

  try { 
    const sk::net::InetSocketAddress endpoint(sk::net::ip4::InetAddress::getLoopbackAddress().resolve(), 8787);
    std::cerr << "Connecting to " << endpoint << std::endl;

    sk::net::Socket socket(endpoint);
    std::cerr << "Connected to " << socket.endpoint() << " (localy: " << socket.localEndpoint() << ")" << std::endl;

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
  }
  catch(const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
  }
  return 0;
}

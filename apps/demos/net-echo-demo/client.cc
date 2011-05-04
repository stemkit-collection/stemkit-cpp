/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Pathname.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/IllegalArgumentException.h>
#include <sk/rt/Scope.h>
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Starter.h>
#include <sk/rt/thread/Joiner.h>
#include <sk/net/InetSocketAddress.h>
#include <sk/net/Socket.h>
#include <sk/io/Console.h>

#include "Producer.h"

#include <sk/util/exception/Tracer.h>
#include <sk/rt/StackTracerFactory.h>

class Reader : public virtual sk::util::Mapper<const sk::util::String>, public virtual sk::rt::Runnable {
  public:
    Reader(const sk::util::String& name, sk::io::InputStream& input, sk::io::OutputStream& output)
      : _scope(name), _producer(name, input, output) {}

    void run() {
      try {
        _producer.start(*this);
      }
      catch(const std::exception& exception) {
        _scope.error() << exception.what();
      }
    }

    const sk::util::String map(const sk::util::String& item) const {
      return _scope.getName() + "> " + item;
    }

  private:
    const sk::rt::Scope _scope;
    echo::Producer _producer;
};

class App {
  public:
    App(const int argc, const char* const argv[]) : _scope("Client"), _socket(figureEndpoint(argc, argv)) {
      _scope.info() << "Connected to " << _socket.endpoint();
    }

    void start() {
      sk::io::Console console;
      sk::util::ArrayList<sk::rt::Thread> threads;

      threads.add(new sk::rt::Thread(new Reader("Console", console.inputStream(), _socket.outputStream())));
      threads.add(new sk::rt::Thread(new Reader("Socket", _socket.inputStream(), console.outputStream())));

      threads.forEach(sk::rt::thread::Starter());
      threads.forEach(sk::rt::thread::Joiner());
    }

  private:
    static const sk::net::InetSocketAddress figureEndpoint(const int argc, const char* const argv[]) {
      if(argc != 3) {
        throw sk::util::IllegalArgumentException("USAGE: " + sk::util::Pathname(argv[0]).basename() + " <host> <port>");
      }
      return sk::net::InetSocketAddress(argv[1], sk::util::Integer::parseInt(argv[2]));
    }
    const sk::rt::Scope _scope;
    sk::net::Socket _socket;
};

int main(int argc, const char* const argv[])
{
  sk::rt::StackTracerFactory factory;
  sk::util::exception::Tracer::setProducerFactory(factory);

  const sk::rt::Scope scope("app");
  try {
    App app(argc, argv);
    app.start();
  }
  catch(const std::exception& exception) {
    scope.error() << exception.what();
    return 2;
  }
  return 0;
}

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/ArrayList.cxx>
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Starter.h>
#include <sk/rt/thread/Joiner.h>
#include <sk/net/Socket.h>
#include <sk/io/Console.h>

#include "Producer.h"
#include "App.h"

class Reader : public virtual sk::util::Mapper<const sk::util::String>, public virtual sk::rt::Runnable {
  public:
    Reader(const sk::util::String& name, sk::io::InputStream& input, sk::io::OutputStream& output)
      : _scope(name), _producer(input, output) {}

    void run() {
      _producer.start(*this);
    }

    const sk::util::String map(const sk::util::String& item) const {
      return _scope.getName() + "> " + item;
    }

  private:
    const sk::rt::Scope _scope;
    echo::Producer _producer;
};

class App : public echo::App {
  public:
    App(const int argc, const char* const argv[]) : echo::App("Client", argc, argv), _socket(endpoint()) {
      scope().info() << "Connected to " << _socket.endpoint();
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
    sk::net::Socket _socket;
};

int main(int argc, const char* const argv[])
{
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

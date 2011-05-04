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
#include <sk/util/IllegalArgumentException.h>
#include <sk/util/Holder.cxx>
#include <sk/util/ArrayList.cxx>
#include <sk/net/ServerSocket.h>
#include <sk/rt/Thread.h>

#include "Producer.h"

class Responder : public virtual sk::util::Mapper<const sk::util::String>, public virtual sk::rt::Runnable {
  public:
    Responder(const sk::net::Socket& socket) : _scope("Responder"), _socket(socket), _producer(_socket.inputStream(), _socket.outputStream()) {
      _scope.info() << "Got connection from " << _socket.endpoint();
    }

    void run() {
      try {
        _producer.start(*this);
      }
      catch(const std::exception& exception) {
        _scope.error() << exception.what();
      }
      _scope.info() << "Terminated connection from " << _socket.endpoint();
    }

    const sk::util::String map(const sk::util::String& line) const {
      return _scope.getName() + "> " + line;
    }

  private:
    const sk::rt::Scope _scope;
    const sk::net::Socket _socket;
    echo::Producer _producer;
};

class App : public virtual sk::util::Selector<sk::rt::Thread> {
  public:
    App(const int argc, const char* const argv[]) : _scope("Server"), _server(figurePort(argc, argv)) {
      _server.setReuseAddress(true);
      _scope.info() << "Listening on " << _server.endpoint();
    }

    void start() {
      while(true) {
        _threads.remove(*this);

        sk::util::Holder<sk::rt::Thread> threadHolder(new sk::rt::Thread(new Responder(_server.accept())));
        threadHolder.getMutable().start();
        _threads.add(threadHolder.release());
      }
    }

  private:
    static uint16_t figurePort(const int argc, const char* const argv[]) {
      if(argc != 2) {
        throw sk::util::IllegalArgumentException("USAGE: " + sk::util::Pathname(argv[0]).basename() + " <port>");
      }
      return sk::util::Integer::parseInt(argv[1]);
    }

    bool assess(const sk::rt::Thread& thread) const {
      return thread.isAlive() == false;
    }

    const sk::rt::Scope _scope;
    sk::net::ServerSocket _server;
    sk::util::ArrayList<sk::rt::Thread> _threads;
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

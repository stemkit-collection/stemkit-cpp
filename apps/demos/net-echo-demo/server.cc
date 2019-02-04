/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Holder.cxx>
#include <sk/util/ArrayList.cxx>
#include <sk/net/ServerSocket.h>
#include <sk/rt/Thread.h>

#include "Producer.h"
#include "App.h"

class Responder : public virtual sk::util::Mapper<const sk::util::String>, public virtual sk::rt::Runnable {
  public:
    Responder(const sk::net::Socket& socket) : _scope("Responder"), _socket(socket), _producer(_socket.inputStream(), _socket.outputStream()) {
      _scope.info() << "Got connection from " << _socket.endpoint();
    }

    void run() {
      bool status = _producer.start(*this);
      _scope.info() << "Terminated connection from " << _socket.endpoint() << " (" << status << ")";
    }

    const sk::util::String map(const sk::util::String& line) const {
      return _scope.getName() + "> " + line;
    }

  private:
    const sk::rt::Scope _scope;
    const sk::net::Socket _socket;
    echo::Producer _producer;
};

class App : public echo::App, public virtual sk::util::Selector<sk::rt::Thread> {
  public:
    App(const int argc, const char* const argv[]) : echo::App("Server", argc, argv), _server(endpoint()) {
      scope().info() << "Listening on " << _server.endpoint();
      _server.setReuseAddress(true);
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
    bool assess(const sk::rt::Thread& thread) const {
      return thread.isAlive() == false;
    }

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

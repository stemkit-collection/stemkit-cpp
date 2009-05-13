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
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/AbstractProcessListener.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <sk/rt/Thread.h>
#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

int start_listener(int port);
int accept_connection(int sock);
void process_request(int sock);

void start(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
  try {
    sk::rt::Scope::controller().loadXmlConfig(
      sk::rt::config::InlineLocator("\n\
        <scope name='app'>\n\
          <log destination='file' eol='windows' level='debug' show-object='true' show-pid='true' show-time='true'>\n\
            <file name='tcp-echo.log' />\n\
          </log>\n\
          \n\
          <scope name='thread-exception-handler'>\n\
            <property name='abort-on-exception' value='false' />\n\
          </scope>\n\
          \n\
          <scope name='sk::rt::thread::pthreads::Mutex'>\n\
            <property name='perform-error-check' value='true' />\n\
          </scope>\n\
          \n\
        </scope>\n\
      ")
    );
    start(argc, argv);
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
}

void start(int argc, const char* argv[]) {
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
    Configurator(sk::rt::Scope& scope, const sk::io::InputStream& inputStream, const sk::io::OutputStream& outputStream)
      : _scope(scope), _inputStream(inputStream), _outputStream(outputStream) 
    {
      _scope.notice() << "Input:  " << sk::util::upcast<sk::io::FileDescriptorProvider>(inputStream).getFileDescriptor().getFileNumber();
      _scope.notice() << "Output: " << sk::util::upcast<sk::io::FileDescriptorProvider>(outputStream).getFileDescriptor().getFileNumber();
    }
    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      configurator.addStream(_inputStream);
      configurator.addStream(_outputStream);
    }
    sk::rt::Scope& _scope;
    const sk::io::InputStream& _inputStream;
    const sk::io::OutputStream& _outputStream;
  };

  struct PipeReader : public virtual sk::rt::Runnable {
    PipeReader(sk::io::InputStream& stream)
      : _scope("PipeReader"), _stream(stream) {}

    void run() {
      while(true) {
        _scope.info("GOT") << _stream.readLine().trim();
      }
    }
    sk::rt::Scope _scope;
    sk::io::DataInputStream _stream;
  };
}

void process_request(int fd) {
  sk::rt::Scope scope(__FUNCTION__);

  sk::io::FileDescriptorInputStream inputStream(fd);
  sk::io::FileDescriptorOutputStream outputStream(inputStream.getFileDescriptor());
  Configurator configurator(scope, inputStream, outputStream);
  
  /*
  sk::io::AnonymousPipe inPipe;
  sk::io::AnonymousPipe outPipe;
  Configurator configurator(scope, outPipe.inputStream(), inPipe.outputStream());
  */
  
  sk::sys::Process process(sk::util::StringArray("tcp-echo-client"), configurator);
  
  inputStream.close();
  outputStream.close();

  /*
  outPipe.closeInput();
  inPipe.closeOutput();

  PipeReader reader(inPipe.inputStream());
  sk::rt::Thread thread(reader);
  thread.start();

  int counter = 0;
  sk::io::DataInputStream stream(inputStream);
  while(true) {
    sk::util::String line = stream.readLine();
    scope.notice("TCP") << line.inspect();

    outPipe.outputStream().write(sk::util::Container("R#" + sk::util::String::valueOf(++counter) + ": " + line.inspect() + "\r\n"));
  }
  */

  process.join();
}

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
#include <cstring>

#include <sk/sys/StreamPortal.h>
#include <sk/sys/Process.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/rt/SystemException.h>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>

void start(int argc, const char* argv[]);
void set_so_rcvbuf(int fd, int size);
void print_so_rcvbuf(int fd);
void print_so_type(int fd);

int main(int argc, const char* argv[])
{
  try {
    sk::rt::Scope::controller().loadXmlConfig(
      sk::rt::config::InlineLocator("\n\
        <scope name='app'>\n\
          <log destination='std::cerr' eol='windows' level='debug' show-object='true' show-pid='true' show-time='true'>\n\
            <file name='tcp-echo.log' />\n\
          </log>\n\
          \n\
          <scope name='thread-exception-handler'>\n\
            <property name='abort-on-exception' value='true' />\n\
          </scope>\n\
          \n\
          <scope name='sk::rt::thread::pthreads'>\n\
            <property name='mutex-error-check' value='true' />\n\
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

void start(int /*argc*/, const char* /*argv*/[]) {
  sk::rt::Scope scope(__FUNCTION__);

  sk::sys::StreamPortal& portal = sk::sys::Process::streamPortal();
  scope.notice() << "Got portal";

  const sk::io::FileDescriptor& id = sk::util::upcast<sk::io::FileDescriptorProvider>(portal.streamProvider(0)).getFileDescriptor();
  const sk::io::FileDescriptor& od = sk::util::upcast<sk::io::FileDescriptorProvider>(portal.streamProvider(1)).getFileDescriptor();
  scope.notice() << "Got file descriptor";

  sk::io::FileDescriptorInputStream inputStream(id.getFileNumber());
  scope.notice() << "Got input";

  sk::io::FileDescriptorOutputStream outputStream(od.getFileNumber());
  scope.notice() << "Got output";

  sk::io::DataInputStream dataInput(inputStream);
  sk::io::DataOutputStream dataOutput(outputStream);

  int ifd = inputStream.getFileDescriptor().getFileNumber();
  int ofd = outputStream.getFileDescriptor().getFileNumber();

  print_so_type(ifd);
  print_so_rcvbuf(ifd);
  set_so_rcvbuf(ifd, 2048);
  print_so_rcvbuf(ifd);

  char buffer[1024];
  sk::util::String line = "HELLO\r\n";
  int n = line.length();
  strcpy(buffer, line.getChars());

  while(true) {
    scope.notice() << "Writing:" << ofd;

    errno = 0;
    int status = ::send(ofd, buffer, n, 0);
    // int status = ::write(ofd, buffer, n);
    if(status < 0) {
      throw sk::rt::SystemException("send");
    }

    for(int c=5; c != 0 ;--c) {
      scope.notice() << "Reading:" << ifd;
      // n = ::read(ifd, buffer, sizeof(buffer));
      errno = 0;
      n = ::recv(ifd, buffer, sizeof(buffer), 0);
      if(!(n<0 && errno==0)) {
        break;
      }
      sleep(1);
    }

    if(n < 0) {
      throw sk::rt::SystemException("recv:n=" + sk::util::String::valueOf(n));
    }
    if(n == 0) {
      scope.notice() << "Done.";
      break;
    }
  }
}

void print_so_type(int fd) {
  sk::rt::Scope scope(__FUNCTION__);

  int value = -77;
  socklen_t value_size = sizeof(value);
  int status = getsockopt(fd, SOL_SOCKET, SO_TYPE, &value, &value_size);

  if(status < 0) {
      throw sk::rt::SystemException("getsockopt");
  }
  scope.notice("SO_TYPE") << value_size << ":value=" << value << ":SOCK_STREAM=" << SOCK_STREAM;
}

void print_so_rcvbuf(int fd) {
  sk::rt::Scope scope(__FUNCTION__);

  int value = -77;
  socklen_t value_size = sizeof(value);
  int status = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &value, &value_size);
  if(status < 0) {
      throw sk::rt::SystemException("getsockopt");
  }
  scope.notice("SO_RCVBUF") << value_size << ":value=" << value;
}

void set_so_rcvbuf(int fd, int size) {
  sk::rt::Scope scope(__FUNCTION__);

  int status = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
  if(status < 0) {
      throw sk::rt::SystemException("setsockopt");
  }
  scope.notice("SO_RCVBUF") << "Attempted to set to " << size;
}

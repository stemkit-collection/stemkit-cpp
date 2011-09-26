/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include "StackTracer.h"

#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>

#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static const sk::util::String __className("sk::rt::StackTracer");

sk::rt::StackTracer::
StackTracer()
  : _scope(__className), _pid(-1), _channel(-1), 
    _finalizeCores(_scope.getProperty("exception-finalize-core", sk::util::Boolean::B_FALSE)),
    _finalizeWaits(_scope.getProperty("exception-finalize-wait", sk::util::Boolean::B_FALSE))
{

}

sk::rt::StackTracer::
~StackTracer()
{
}

const sk::util::Class
sk::rt::StackTracer::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  void produce_system_error(bool exception, const sk::util::Strings& info) {
    sk::util::Strings items;
    int index = 0;

    items << (info.size() > index ? info.get(index++) : sk::util::String("???"));
    items << sk::util::String::valueOf(errno);
    items << ::strerror(errno);
    items << info.slice(index, -1);

    if(exception == true) {
      throw std::domain_error(items.join(": "));
    }
    std::cerr << items.join("<", ": ", ">") << std::endl;
  }

  void generate_system_error(const sk::util::Strings& info) {
    produce_system_error(true, info);
  }

  void print_system_error(const sk::util::Strings& info) {
    produce_system_error(false, info);
  }

  void collect_chars_until_eof(int fd, std::ostream& stream) {
    char buffer[1024];
    while(true) {
      int n = read(fd, &buffer, sizeof(buffer) - 1);
      if(n == -1) {
        if(errno = EINTR) {
          continue;
        }
        break;
      }
      if(n == 0) {
        break;
      }
      buffer[n] = 0;
      stream << buffer;
    }
  }

  void wait_for_process(const sk::util::String& label, pid_t pid) {
    while(true) {
      pid_t status = ::waitpid(pid, 0, 0);
      if(status == -1) {
        if(errno == EINTR) {
          continue;
        }
        generate_system_error(sk::util::Strings("waitpid") << label << sk::util::String::valueOf(pid));
      }
      if(status == pid) {
        return;
      }
      std::stringstream stream;
      stream << "Wrong process: need " << pid << ", got " << status;
      throw std::domain_error(stream.str());
    }
  }

  const sk::util::String dumpCoreRequest() {
    return "dump-core";
  }

}

void
sk::rt::StackTracer::
setup()
{
  if(_pid != -1) {
    return;
  }

  int fds[2];
  if(::pipe(fds) != 0) {
    generate_system_error("pipe");
  }

  pid_t pid = ::fork();
  switch(pid) {
    case -1: {
      generate_system_error("fork");
    }
    case 0: {
      ::close(fds[1]);
      std::stringstream stream;
      collect_chars_until_eof(fds[0], stream);
      if(sk::util::String(stream.str()).trim() == dumpCoreRequest()) {
        ::abort();
      }
      _exit(0);
    }
    default: {
      ::close(fds[0]);
      _channel = fds[1];
      _pid = pid;
    }
  }
}

void 
sk::rt::StackTracer::
reset()
{
  if(_pid == -1) {
    return;
  }
  ::close(_channel);
  _channel = -1;

  pid_t pid = _pid;
  _pid = -1;

  wait_for_process("clone", pid);
}

const sk::util::String
sk::rt::StackTracer::
produceTrace()
{
  if(_pid == -1) {
    throw std::domain_error("setup not done");
  }

  int fds[2];
  if(::pipe(fds) != 0) {
    generate_system_error("pipe");
  }

  pid_t pid = fork();
  switch(pid) {
    case -1: {
      generate_system_error("fork");
    }
    case 0: {
      close(fds[0]);
      close(1);
      close(2);
      dup(fds[1]);
      dup(fds[1]);

      sk::util::String argv0("pstack");
      sk::util::String argv1(sk::util::String::valueOf(_pid));

      ::execlp(argv0.getChars(), argv0.getChars(), argv1.getChars(), (const char*)0);
      print_system_error(sk::util::Strings("execlp") << argv0);
      _exit(2);
    }
    default: {
      close(fds[1]);
    }
  }
  std::stringstream stream;
  collect_chars_until_eof(fds[0], stream);
  wait_for_process("pstack", pid);

  return stream.str();
}

void
sk::rt::StackTracer::
finalize()
{
  if(_pid == -1) {
    return;
  }

  pid_t thisPid = ::getpid();

  do {
    if(_finalizeWaits == true) {

      sk::util::Strings message("Suspending processes");
      message << sk::util::String::valueOf(thisPid);
      message << sk::util::String::valueOf(_pid);

      _scope.notice() << message.join(": ");

      while(true) {
        ::kill(thisPid, SIGSTOP);
        ::sleep(60);
      }
      break;
    }

    if(_finalizeCores == true) {
      sk::util::Strings message("Dumping core");
      message << sk::util::String::valueOf(thisPid);
      message << sk::util::String::valueOf(_pid);

      _scope.notice() << message.join(": ");

      const sk::util::String request = dumpCoreRequest();
      ::write(_channel, request.getChars(), request.length());

      break;
    }
  } while(false);

  reset();
}

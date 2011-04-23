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
#include <sk/util/Holder.cxx>

#include "../StackTracer.h"

#include <stdexcept>
#include <cerrno>
#include <iostream>
#include <sstream>

#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

static const sk::util::String __className("sk::rt::StackTracer");

struct sk::rt::StackTracer::Data : public virtual sk::util::Object {
  int channel;
  pid_t pid;
};

sk::rt::StackTracer::
StackTracer()
  : _dataHolder(new Data), _data(_dataHolder.getMutable())
{
  _data.pid = -1;
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
  void produce_system_error(bool exception, const sk::util::String& label, const sk::util::String& info) {
    sk::util::Strings items;

    items << label;
    items << sk::util::String::valueOf(errno);
    items << strerror(errno);

    if(&info != &sk::util::String::EMPTY) {
      items << info;
    }
    if(exception == true) {
      throw std::domain_error(items.join(": "));
    }
    std::cerr << items.join("<", ": ", ">") << std::endl;
  }

  void generate_system_error(const sk::util::String& label, const sk::util::String& info = sk::util::String::EMPTY) {
    produce_system_error(true, label, info);
  }

  void print_system_error(const sk::util::String& label, const sk::util::String& info = sk::util::String::EMPTY) {
    produce_system_error(false, label, info);
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

  void wait_for_process(pid_t pid) {
    while(true) {
      pid_t status = ::waitpid(pid, 0, 0);
      if(status == -1) {
        if(errno == EINTR) {
          continue;
        }
        generate_system_error("waitpid");
      }
      if(status == pid) {
        return;
      }
      std::stringstream stream;
      stream << "Wrong process: need " << pid << ", got " << status;
      throw std::domain_error(stream.str());
    }
  }

}

void
sk::rt::StackTracer::
setup()
{
  if(_data.pid != -1) {
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
      _exit(0);
    }
    default: {
      ::close(fds[0]);
      _data.channel = fds[1];
      _data.pid = pid;
    }
  }
}

void 
sk::rt::StackTracer::
reset()
{
  if(_data.pid == -1) {
    return;
  }
  pid_t pid = _data.pid;
  _data.pid = -1;

  ::close(_data.channel);
  wait_for_process(pid);
}

const sk::util::String
sk::rt::StackTracer::
produceTrace()
{
  if(_data.pid == -1) {
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
      sk::util::String argv1(sk::util::String::valueOf(_data.pid));

      ::execlp(argv0.getChars(), argv0.getChars(), argv1.getChars(), (const char*)0);
      print_system_error("execlp", argv0);
      _exit(2);
    }
    default: {
      close(fds[1]);
    }
  }
  std::stringstream stream;
  collect_chars_until_eof(fds[0], stream);
  wait_for_process(pid);

  return stream.str();
}


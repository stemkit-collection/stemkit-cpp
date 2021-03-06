/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Processor.h>
#include <sk/util/ArrayList.cxx>
#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include "Spawner.h"
#include <iostream>

static const char* __className("test::Spawner");

test::Spawner::
Spawner(int argc, const char* argv[])
  : _counter(0)
{
}

test::Spawner::
~Spawner()
{
}

const sk::util::Class
test::Spawner::
getClass() const
{
  return sk::util::Class(__className);
}

void
test::Spawner::
start()
{
  perform();
}

namespace {
  struct Configurator : public sk::sys::AbstractProcessListener {
    Configurator(sk::io::Pipe& pipe)
      : _pipe(pipe) {}

    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      configurator.setOutputStream(_pipe.outputStream());
    }

    void processStarting(sk::io::Stream& umbilical) {
      umbilical.close();
      _pipe.close();
    }

    sk::io::Pipe& _pipe;
  };

  struct Block : public virtual sk::rt::Runnable {
    Block(int id, sk::io::Pipe& pipe)
      : _configurator(pipe), _process(sk::util::Strings("ksh") + "-c" + figureScript(id), _configurator) {}

    static const sk::util::String figureScript(int id) {
      sk::util::String location(getenv("JAM_SRCDIR"));
      if(location.isEmpty() == true) {
        location = ".";
      }
      return location + "/" + "worker.sh " + sk::util::String::valueOf(id);
    }

    void run() {
      _process.join();
    }

    Configurator _configurator;
    sk::sys::Process _process;
  };

  struct Starter : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.start();
    }
  };

  struct Joiner : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.join();
    }
  };

  struct Reader : public virtual sk::rt::Runnable {
    Reader(sk::io::InputStream& stream)
      : _stream(stream) {}

    void run() {
      try {
        while(true) {
          std::cerr << "I: " << _stream.readLine().trim() << std::endl;
        }
      }
      catch(const sk::io::EOFException& exception) {}
    }
    sk::io::DataInputStream _stream;
  };
}

void
test::Spawner::
perform()
{
  sk::io::AnonymousPipe pipe;
  sk::rt::Thread reader(new Reader(pipe.inputStream()));
  reader.start();

  sk::util::ArrayList<sk::rt::Thread> writers;

  for(int counter=10; counter ; --counter) {
    writers.add(new sk::rt::Thread(new Block(++_counter, pipe)));
  }
  writers.forEach(Starter());
  pipe.closeOutput();

  writers.forEach(Joiner());
  reader.join();
}


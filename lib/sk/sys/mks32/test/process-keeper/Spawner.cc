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

static const char* __className("test::Spawner");

test::Spawner::
Spawner(int argc, const char* argv[])
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

    sk::io::Pipe& _pipe;
  };

  struct Block : public virtual sk::rt::Runnable {
    Block(sk::io::Pipe& pipe) 
      : _scope("Block"), _configurator(pipe), _process(sk::util::StringArray("date"), _configurator) {}

    void run() {
      _process.join();
      _scope.info() << "Process done";
    }

    sk::rt::Scope _scope;
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
      : _scope("Reader"), _stream(stream) {}

    void run() {
      try { 
        while(true) {
          _scope.info("D") << _stream.readLine().trim();
        }
      }
      catch(const sk::io::EOFException& exception) {}
    }
    sk::io::DataInputStream _stream;
    sk::rt::Scope _scope;
  };
}

void 
test::Spawner::
perform()
{
  while(true) {
    sk::io::AnonymousPipe pipe;
    sk::rt::Thread reader(new Reader(pipe.inputStream()));
    reader.start();

    sk::util::ArrayList<sk::rt::Thread> writers;

    for(int counter=10; counter ; --counter) {
      writers.add(new sk::rt::Thread(new Block(pipe)));
    }
    writers.forEach(Starter());
    pipe.closeOutput();

    writers.forEach(Joiner());
    reader.join();
  }
}


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

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/Thread.h>

void perform();

int main(int /*argc*/, const char* /*argv*/[])
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <scope name='sk::rt::thread::pthread::Mutex'>\n\
          <log destination='std::cerr' level='error' show-object='false' show-time='true' />\n\
        </scope>\n\
        <scope name='sk::rt::thread::pthread::Thread'>\n\
          <log destination='std::cerr' level='error' show-object='false' show-time='true' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );

  while(true) {
    perform();
  }
  sk::rt::Thread::reset();
}

namespace {
  struct Printer : public virtual sk::rt::Runnable {
    void run() {
      std::cerr << sk::rt::Thread::currentThread().inspect() << std::endl;
    }
  };
}

void perform()
{
  Printer printer;
  sk::rt::Thread thread(printer);

  thread.start();
  thread.detach();

  sk::rt::Thread::sleep(10);
}

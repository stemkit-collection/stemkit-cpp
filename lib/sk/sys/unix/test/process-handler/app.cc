/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/rt/Thread.h>
#include <sk/rt/Scope.h>
#include <sk/rt/thread/ScopeArbitrator.h>
#include <sk/rt/config/InlineLocator.h>

#include "Handler.h"

int main(int argc, const char* argv[])
{
  sk::rt::Thread::setup();

  sk::rt::Scope::controller().getAggregator().setArbitrator(new sk::rt::thread::ScopeArbitrator);
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope>\n\
        <log destination='std::cerr' level='debug' show-memory='false' show-pid='true' show-thread='true' show-object='true'>\n\
          <file name='handler.log' chunks='0' size='0' policy='pointing' ensure-chunks='true' />\n\
        </log>\n\
        <scope name='thread-exception-handler'>\n\
          <property name='abort-on-exception' value='true' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );
  test::Handler app(argc, argv);
  app.start();

  sk::rt::Thread::reset();
}

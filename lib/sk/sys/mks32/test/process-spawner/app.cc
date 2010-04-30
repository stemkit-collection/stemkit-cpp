/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include "Spawner.h"
#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

#include <sk/rt/Thread.h>
#include <sk/sys/Process.h>

int main(int argc, const char* argv[])
{
  try {
    sk::rt::Scope::controller().loadXmlConfig(
      sk::rt::config::InlineLocator("\n\
        <scope>\n\
          <log destination='std::cerr' level='debug' />\n\
          <scope name='thread-exception-handler'>\n\
            <property name='abort-on-exception' value='true' />\n\
          </scope>\n\
        </scope>\n\
      ")
    );
    sk::rt::Thread::setup();
    sk::sys::Process::setup();

    test::Spawner app(argc, argv);
    app.start();
  }
  catch(const std::exception& exception) {
    std::cerr << "E: " << exception.what() << std::endl;
  }
  catch(const std::string& message) {
    std::cout << message << std::endl;
  }
  catch(...) {
    std::cerr << "Unknown error" << std::endl;
  }
  sk::sys::Process::reset();
  sk::rt::Thread::reset();
}

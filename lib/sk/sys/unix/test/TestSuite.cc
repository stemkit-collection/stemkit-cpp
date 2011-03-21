/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/Thread.h>

#include <iostream>
 
int main(int argc, char **argv)
{     
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  sk::cppunit::TestRunner runner;

  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <log destination='std::cerr' eol='windows' level='info' show-object='true' show-time='true'>\n\
          <file name='test.log' />\n\
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
        <scope name='sk::sys::DaemonProcess'>\n\
          <property name='trash-output' value='false' />\n\
        </scope>\n\
        \n\
      </scope>\n\
    ")
  );

  if(argc == 2) {
    sk::cppunit::SourcePath::setBase(argv[1]);
  }
  runner.addTest(registry.makeTest());
  sk::rt::Thread::setup();

  int status = !runner.run();
  sk::rt::Thread::reset();
  return status;
}

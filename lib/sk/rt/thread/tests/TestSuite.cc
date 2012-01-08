/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>

#include <iostream>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/Thread.h>

int main(int argc, const char* argv[])
{
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  sk::cppunit::TestRunner runner;

  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <log destination='file' eol='windows' level='debug' show-object='false' show-time='true'>\n\
          <file name='test.log' />\n\
        </log>\n\
        \n\
        <scope name='thread-exception-handler'>\n\
          <property name='abort-on-exception' value='false' />\n\
        </scope>\n\
        \n\
        <scope name='sk::rt::thread'>\n\
          <property name='generic-condition-mediator' value='true' />\n\
        </scope>\n\
        <scope name='sk::rt::thread::pthreads'>\n\
          <property name='mutex-error-check' value='true' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );

  if(argc == 2) {
    sk::cppunit::SourcePath::setBase(argv[1]);
  }
  runner.addTest(registry.makeTest());
  return !runner.run();
}

/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/String.h>
#include <sk/rt/StackTracerFactory.h>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

void showSpot(const sk::rt::Scope& scope) {
  scope.info("Stack trace").stackTrace();
}

int main(int argc, const char* const argv[])
{
  sk::util::Exception::setTraceProducerFactory(sk::rt::StackTracerFactory());
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator(
      "<scope>\n"
      "  <log destination='std::cerr' level='notice' show-thread='true' show-time='true' />\n"
      "  <property name='exception-must-core' value='true' />\n"
      "  <property name='exception-must-wait' value='true' />\n"
      "</scope>\n"
    )
  );

  sk::rt::Scope scope("main");

  try {
    showSpot(scope);

    sk::util::Strings items("abc");
    scope.info() << items.get(1);
  }
  catch(const sk::util::Exception& exception) {
    scope.error() << exception.what();
    exception.finalize();
  }
  return 0;
}

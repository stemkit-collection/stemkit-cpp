/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
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

#include <sk/util/Strings.h>
#include <sk/util/exception/Tracer.h>
#include <sk/rt/StackTracerFactory.h>

int main(int argc, const char* const argv[])
{
  sk::util::exception::Tracer::setProducerFactory(sk::rt::StackTracerFactory());

  try {
    sk::util::Strings items("abc");
    std::cerr << items.get(1) << std::endl;
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
  return 0;
}

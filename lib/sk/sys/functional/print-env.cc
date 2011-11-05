/*  vim: sw=4:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <sk/rt/Environment.h>

int main(int argc, const char* const argv[])
{
  struct Printer : public virtual sk::util::BinaryProcessor<const sk::util::String, const sk::util::String> {
      void process(const sk::util::String& key, const sk::util::String& value) const {
          std::cout << key.inspect() << "=" << value.inspect() << std::endl;
      }
  };
  sk::rt::Environment().forEach(Printer());
  return 0;
}

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
#include <sk/rt/Mutex.h>

int sample_f();

int abc = sample_f();

sk::rt::Mutex _mutex;

int main(int argc, const char* argv[])
{
  try {
    throw std::string("Hello, world!!!");
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
}

int sample_f()
{
  fprintf(stderr, ">>> sample_f()\n");
  return 5;
}

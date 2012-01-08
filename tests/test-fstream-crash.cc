/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <iostream>
#include <fstream>
#include <memory>

class MyStream
{
  public:
    MyStream(const char* name)
      : _stream(name) {}

  private:
    std::ifstream _stream;
};

int main(int argc, char **argv)
{
  try {
    // MyStream* stream = new MyStream("abc"); // NO CRASH
    std::ifstream* stream = new std::ifstream("abc"); // CRASH
    std::cerr << ">>> OPENED: " << stream << std::endl;
    delete stream;
    std::cerr << ">>> DELETED" << std::endl;
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
  std::cerr << ">>> CLEANED" << std::endl;
  return 0;
}

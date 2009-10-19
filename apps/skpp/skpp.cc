/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>
#include <sk/util/PrettyPrinter.h>
#include <iostream>

int main(int argc, const char* argv[])
{
  sk::util::PrettyPrinter printer(std::cout);
  sk::io::FileDescriptorInputStream input(0);
  sk::io::DataInputStream stream(input);

  try {
    while(true) {
      printer.print(stream.readLine());
    }
  }
  catch(const sk::io::EOFException& exception) {}

  return 0;
}

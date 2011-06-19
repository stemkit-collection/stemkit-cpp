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
#include <sk/util/IllegalArgumentException.h>
#include <sk/util/Pathname.h>
#include <sk/util/PrettyPrinter.h>
#include <sk/io/FileInfo.h>
#include <sk/io/Dir.h>

namespace {
  struct Printer : public virtual sk::util::Processor<const sk::io::FileInfo> {
    void process(const sk::io::FileInfo& info) const {
      std::cout << info << std::endl;
    }
  };

  struct PrettyPrinter : public virtual sk::util::Processor<const sk::io::FileInfo> {
    PrettyPrinter() 
      : _printer(std::cout) {}

    void process(const sk::io::FileInfo& info) const {
      _printer.print(info.inspect());
    }
    sk::util::PrettyPrinter _printer;
  };
}

int main(int argc, const char* argv[])
{
  sk::util::Pathname program(argv[0]);
  try {
    if(argc != 2) {
      throw sk::util::IllegalArgumentException("USAGE: " + program.basename() + " <directory>");
    }
    sk::io::Dir dir(argv[1]);
    dir.forEachDirectory(Printer());
    dir.forEachRegularFile(Printer());
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
}

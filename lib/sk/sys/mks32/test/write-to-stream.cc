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

#include <sk/util/IllegalArgumentException.h>
#include <sk/util/Container.h>
#include <sk/sys/Process.h>
#include <sk/sys/StreamPortal.h>
#include <sk/io/OutputStream.h>

int main(int argc, const char* argv[])
{
  try {
    if(argc != 2) {
      throw sk::util::IllegalArgumentException("main()");
    }
    sk::sys::StreamPortal& portal = sk::sys::Process::streamPortal();
    sk::io::OutputStream& outputStream = portal.outputStream(0);

    outputStream.write(sk::util::Container(sk::util::String(argv[1]) + "\r\n"));
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
  return 0;
}

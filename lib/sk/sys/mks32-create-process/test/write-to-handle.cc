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
#include <sstream>
#include <winnutc.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
  if(argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " <handle> <message>" << std::endl;
    return 2;
  }
  int descriptor = 0;
  std::istringstream(argv[1]) >> descriptor;
  HANDLE handle = reinterpret_cast<HANDLE>(descriptor);

  if(SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0) == 0) {
    std::cerr << argv[0] << ":" << "Invalid handle:" << handle << ":" << descriptor << std::endl;
    return 3;
  }
  int fd = ::_NutHandleToFd(handle, O_RDWR, "");
  int len = strlen(argv[2]);

  if(::write(fd, argv[2], len) != len) {
    std::cerr << argv[0] << ":" << len << ":Write failed:" << handle << ":" << descriptor << ":" << fd << std::endl;
    return 4;
  }
  std::cout << descriptor << ":" << handle << ":" << fd << ":" << argv[2] << std::endl;
  return 0;
}

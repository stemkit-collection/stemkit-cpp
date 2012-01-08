/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/net/InetAddress.h>

int main(int argc, const char* const argv[])
{
  const sk::net::InetAddress& address = sk::net::InetAddress::getLocalHost();
  std::cerr << "A: " << address << std::endl;

  return 0;
}

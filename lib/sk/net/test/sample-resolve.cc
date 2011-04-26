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

const std::vector<int> operator + (const std::vector<int>& container, int value) {
  std::vector<int> result(container);
  result.push_back(value);
  return result;
}

int main(int argc, const char* const argv[])
{
  sk::net::InetAddress& address = sk::net::InetAddress::getByAddress(std::vector<int>() + 1 + 2 + 3 + 4);
  std::cerr << "A: " << address << std::endl;

  return 0;
}

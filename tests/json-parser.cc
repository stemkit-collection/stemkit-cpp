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
#include <sk/other/jsoncpp/json/json.h>

int main(int argc, const char* const argv[])
{
  if(argc != 2) {
    std::cerr << "USAGE: json-parser <string>" << std::endl;
    exit(2);
  }
  Json::Value root;
  Json::Reader reader;

  if(reader.parse(argv[1], root) == false) {
    std::cerr << reader.getFormatedErrorMessages();
  }

  std::cout << "JSON: " << root << std::endl;
}

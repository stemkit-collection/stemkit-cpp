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

#include <sk/other/yaml-cpp/yaml.h>

int main(int argc, const char* argv[])
{
  SK_YAML::Emitter out;
  out << SK_YAML::BeginMap;
  out << SK_YAML::Key << "items" << SK_YAML::Value;
  out << SK_YAML::BeginSeq;
  out << "aaa";
  out << "bbb";
  out << "ccc";

  out << SK_YAML::BeginMap;
  out << SK_YAML::Key << "v1" << SK_YAML::Value << "aaa";
  out << SK_YAML::Key << "v2" << SK_YAML::Value << "aaa";
  out << SK_YAML::Key << "v3" << SK_YAML::Value << "aaa";
  out << SK_YAML::EndMap;

  out << SK_YAML::EndSeq;
  out << SK_YAML::EndMap;

  std::cerr << out.c_str() << std::endl;
}

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
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "items" << YAML::Value;
  out << YAML::BeginSeq;
  out << "aaa";
  out << "bbb";
  out << "ccc";

  out << YAML::BeginMap;
  out << YAML::Key << "v1" << YAML::Value << "aaa";
  out << YAML::Key << "v2" << YAML::Value << "aaa";
  out << YAML::Key << "v3" << YAML::Value << "aaa";
  out << YAML::EndMap;

  out << YAML::EndSeq;
  out << YAML::EndMap;

  std::cerr << out.c_str() << std::endl;
}

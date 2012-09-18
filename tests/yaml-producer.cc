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
  LOCAL_YAML::Emitter out;
  out << LOCAL_YAML::BeginMap;
  out << LOCAL_YAML::Key << "items" << LOCAL_YAML::Value;
  out << LOCAL_YAML::BeginSeq;
  out << "aaa";
  out << "bbb";
  out << "ccc";

  out << LOCAL_YAML::BeginMap;
  out << LOCAL_YAML::Key << "v1" << LOCAL_YAML::Value << "aaa";
  out << LOCAL_YAML::Key << "v2" << LOCAL_YAML::Value << "aaa";
  out << LOCAL_YAML::Key << "v3" << LOCAL_YAML::Value << "aaa";
  out << LOCAL_YAML::EndMap;

  out << LOCAL_YAML::EndSeq;
  out << LOCAL_YAML::EndMap;

  std::cerr << out.c_str() << std::endl;
}

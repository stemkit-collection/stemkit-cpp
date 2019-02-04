/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/File.h>
#include <sk/util/StringArray.h>

#include <iostream>

void print_memory(const sk::util::String& label)
{
  static sk::util::String statfile = "/proc/" + sk::util::String::valueOf(getpid()) + "/stat";
  sk::util::File f(statfile);
  std::cerr << sk::util::Integer::parseInt(f.getLine().split().get(22))/1024 << std::endl;

  getchar();
}

int main(int argc, const char* argv[])
{
  print_memory("A");

  char* c = new char[1024*1024*1024];

  print_memory("B");
}

/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <stdio.h>

int main(int argc, const char* argv[])
{
  int index = 0;
  while(index < argc) {
    const char* item = argv[index++];

    if(item) {
      printf("\"%s\"\n", item);
    }
    else printf("<null>\n");
  }
  return 0;
}

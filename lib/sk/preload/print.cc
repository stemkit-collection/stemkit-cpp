/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <iostream>
#include <unistd.h>

namespace sk {
  namespace preload {
    class Printer
    {
      public:
        Printer();
        virtual ~Printer();
    };
  }
}

static sk::preload::Printer printer;

sk::preload::Printer::
Printer()
{
  std::cerr << "sk::preload::Printer(), pid=" << getpid() << std::endl;
}

sk::preload::Printer::
~Printer()
{
  std::cerr << "sk::preload::~Printer(), pid=" << getpid() << std::endl;
}

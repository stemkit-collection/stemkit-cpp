/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <unistd.h>

namespace sk {
  namespace preload {
    class Controller
    {
      public:
        Controller();
        virtual ~Controller();

      private:
        void process_recursion_depth();
    };
  }
}

static sk::preload::Controller controller;

sk::preload::Controller::
Controller()
{
  process_recursion_depth();
}

void 
sk::preload::Controller::
process_recursion_depth()
{
  const char* depth = getenv("LD_PRELOAD_DEPTH");
  if(depth && getenv("LD_PRELOAD")) {
    int value = 0;
    int oldpid = 0;

    sscanf(depth, "%d:%d", &value, &oldpid);
    if(value <= 0) {
      return;
    }

    int pid = getpid();
    if(oldpid == pid) {
      return;
    }

    --value;

    std::stringstream stream;
    stream << "LD_PRELOAD_DEPTH=" << value << ":" << pid;
    putenv(const_cast<char*>((new std::string(stream.str()))->c_str()));

    if(value == 0) {
      putenv("LD_PRELOAD=");
    }
  }
}

sk::preload::Controller::
~Controller()
{
}

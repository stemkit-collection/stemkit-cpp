/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_FILE_H_
#define _SK_UTIL_FILE_H_

#include <sk/util/String.h>
#include <fstream>

namespace sk {
  namespace util {
    class File
    {
      public:
        File(const sk::util::String& name);
        static bool exists(const sk::util::String& name);
        static void create(const sk::util::String& name);

        const sk::util::String getLine();
        const sk::util::String getLines(int number);
        const sk::util::String getLines();

      private:
        const sk::util::String _name;
        std::ifstream _file;
    };
  }
}

#endif /* _SK_UTIL_FILE_H_ */

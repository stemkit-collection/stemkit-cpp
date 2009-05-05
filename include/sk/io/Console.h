/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_CONSOLE_H_
#define _SK_IO_CONSOLE_H_

#include <sk/io/File.h>

namespace sk {
  namespace io {
    class Console 
      : public sk::io::File
    {
      public:
        Console();
        virtual ~Console();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Console(const Console& other);
        Console& operator = (const Console& other);
    };
  }
}

#endif /* _SK_IO_CONSOLE_H_ */

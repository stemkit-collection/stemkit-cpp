/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_CONSOLEOUTPUTSTREAM_H_
#define _SK_IO_CONSOLEOUTPUTSTREAM_H_

#include <sk/io/FileOutputStream.h>

namespace sk {
  namespace io {
    class ConsoleOutputStream 
      : public sk::io::FileOutputStream
    {
      public:
        ConsoleOutputStream();
        virtual ~ConsoleOutputStream();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        ConsoleOutputStream(const ConsoleOutputStream& other);
        ConsoleOutputStream& operator = (const ConsoleOutputStream& other);
    };
  }
}

#endif /* _SK_IO_CONSOLEOUTPUTSTREAM_H_ */

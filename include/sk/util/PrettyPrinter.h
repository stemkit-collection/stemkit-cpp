/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PRETTYPRINTER_H_
#define _SK_UTIL_PRETTYPRINTER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class PrettyPrinter 
      : public virtual sk::util::Object
    {
      public:
        PrettyPrinter();
        virtual ~PrettyPrinter();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        PrettyPrinter(const PrettyPrinter& other);
        PrettyPrinter& operator = (const PrettyPrinter& other);
    };
  }
}

#endif /* _SK_UTIL_PRETTYPRINTER_H_ */

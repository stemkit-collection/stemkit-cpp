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
#include <sk/util/slot/Pointer.hxx>
#include <ostream>

namespace sk {
  namespace util {
    namespace pp {
      class Configurator;
    }
    class PrettyPrinter 
      : public virtual sk::util::Object
    {
      public:
        PrettyPrinter(std::ostream& stream);
        virtual ~PrettyPrinter();

        void setCompact(bool state);
        void print(const sk::util::String& input) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        PrettyPrinter(const PrettyPrinter& other);
        PrettyPrinter& operator = (const PrettyPrinter& other);

        std::ostream& _stream;
        sk::util::slot::Pointer<pp::Configurator> _configuratorSlot;
    };
  }
}

#endif /* _SK_UTIL_PRETTYPRINTER_H_ */

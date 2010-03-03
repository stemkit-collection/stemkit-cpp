/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_SYS_STREAMPORTALEXPORTER_H_
#define _SK_SYS_STREAMPORTALEXPORTER_H_

#include <sk/util/String.h>
#include <sk/util/Strings.h>
#include <sk/util/Processor.h>
#include <sk/util/ArrayList.hxx>
#include <sk/io/Stream.h>

#include "StreamPortalPropagator.h"

namespace sk {
  namespace sys {
    class StreamPortalExporter 
      : public virtual sk::util::Processor<const sk::io::Stream> 
    {
      public:
        StreamPortalExporter(sk::util::Strings& descriptors);
    
        // sk::util::Processor implementation.
        void process(const sk::io::Stream& stream) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StreamPortalExporter& operator = (const StreamPortalExporter& other);

        sk::util::Strings& _descriptors;
        sk::sys::StreamPortalPropagator _propagator;
    };
  }
}

#endif /* _SK_SYS_STREAMPORTALEXPORTER_H_ */

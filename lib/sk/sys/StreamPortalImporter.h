/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_SYS_STREAMPORTALIMPORTER_H_
#define _SK_SYS_STREAMPORTALIMPORTER_H_

#include <sk/util/String.h>
#include <sk/util/Processor.h>
#include <sk/util/ArrayList.hxx>
#include <sk/io/Stream.h>

namespace sk {
  namespace sys {
    class StreamPortalImporter 
      : public virtual sk::util::Processor<const sk::util::String> 
    {
      public:
        StreamPortalImporter(sk::util::ArrayList<sk::io::Stream>& streams);
    
        // sk::util::Processor implementation.
        void process(const sk::util::String& descriptor) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StreamPortalImporter& operator = (const StreamPortalImporter& other);

        sk::util::ArrayList<sk::io::Stream>& _streams;
    };
  }
}

#endif /* _SK_SYS_STREAMPORTALIMPORTER_H_ */

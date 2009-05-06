/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_STREAMPORTAL_H_
#define _SK_SYS_STREAMPORTAL_H_

#include <sk/util/Object.h>
#include <sk/util/Processor.h>
#include <sk/io/Stream.h>

namespace sk {
  namespace sys {
    class StreamPortal 
      : public virtual sk::util::Object
    {
      public:
        StreamPortal();
        virtual ~StreamPortal();

        int size() const;
        sk::io::Stream& get(int index) const;
        void forEach(const sk::util::Processor<sk::io::Stream>& stream) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StreamPortal(const StreamPortal& other);
        StreamPortal& operator = (const StreamPortal& other);
    };
  }
}

#endif /* _SK_SYS_STREAMPORTAL_H_ */

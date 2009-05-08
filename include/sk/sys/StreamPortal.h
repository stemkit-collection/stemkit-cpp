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
#include <sk/util/ArrayList.hxx>
#include <sk/util/PropertyRegistry.h>
#include <sk/util/Processor.h>
#include <sk/io/Stream.h>

namespace sk {
  namespace sys {
    class StreamPortal 
      : public virtual sk::util::Object
    {
      public:
        StreamPortal(const sk::util::PropertyRegistry& registry);
        virtual ~StreamPortal();

        static void exportStreams(const sk::util::List<const sk::io::Stream>& streams, sk::util::PropertyRegistry& registry);
        static void clear();

        int size() const;
        sk::io::Stream& getStream(int index) const;
        void forEachStream(const sk::util::Processor<sk::io::Stream>& processor) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StreamPortal(const StreamPortal& other);
        StreamPortal& operator = (const StreamPortal& other);

        void populateFrom(const sk::util::PropertyRegistry& registry);

        sk::util::ArrayList<sk::io::Stream> _streams;
    };
  }
}

#endif /* _SK_SYS_STREAMPORTAL_H_ */

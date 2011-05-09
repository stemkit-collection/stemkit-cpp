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
#include <sk/util/Strings.h>
#include <sk/util/PropertyRegistry.h>
#include <sk/util/Processor.h>
#include <sk/io/StreamProvider.h>
#include <sk/io/Stream.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace sys {
    class StreamPortal 
      : public virtual sk::util::Object
    {
      public:
        StreamPortal(sk::util::PropertyRegistry& registry);
        virtual ~StreamPortal();

        static void exportStreams(const sk::util::List<sk::io::Stream>& streams, sk::util::PropertyRegistry& registry);
        static void clear();
        static sk::rt::Scope& scope();

        int size() const;
        const sk::io::StreamProvider& streamProvider(int index) const;
        sk::io::StreamProvider& streamProvider(int index);

        sk::io::InputStream& inputStream(int index) const;
        sk::io::OutputStream& outputStream(int index) const;
        void forEachStreamProvider(const sk::util::Processor<const sk::io::StreamProvider>& processor) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        StreamPortal(const StreamPortal& other);
        StreamPortal& operator = (const StreamPortal& other);

        void importStreams(const sk::util::PropertyRegistry& registry);
        static const sk::util::Strings descriptors(const sk::util::PropertyRegistry& registry);

        sk::util::ArrayList<sk::io::StreamProvider> _streamProviders;
    };
  }
}

#endif /* _SK_SYS_STREAMPORTAL_H_ */

/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_SYSTEMSTREAMPROVIDER_
#define _SK_IO_SYSTEMSTREAMPROVIDER_

#include <sk/util/Holder.hxx>
#include <sk/io/StandardStreamProvider.h>

namespace sk {
  namespace io {
    class Pipe;

    class SystemStreamProvider
      : public virtual sk::io::StandardStreamProvider
    {
      public:
        SystemStreamProvider();
        virtual ~SystemStreamProvider();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::StandardStreamProvider implementation.
        sk::io::Pipe& getStdin() const;
        sk::io::Pipe& getStdout() const;
        sk::io::Pipe& getStderr() const;
        
      private:
        SystemStreamProvider(const SystemStreamProvider& other);
        SystemStreamProvider& operator = (const SystemStreamProvider& other);

        void initStdin();
        void initStdout();
        void initStderr();

        sk::util::Holder<sk::io::Pipe> _stdinHolder;
        sk::util::Holder<sk::io::Pipe> _stdoutHolder;
        sk::util::Holder<sk::io::Pipe> _stderrHolder;
    };
  }
}

#endif /* _SK_IO_SYSTEMSTREAMPROVIDER_ */

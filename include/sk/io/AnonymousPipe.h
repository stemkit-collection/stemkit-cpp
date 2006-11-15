/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_ANONYMOUSPIPE_
#define _SK_IO_ANONYMOUSPIPE_

#include <sk/util/Holder.hxx>
#include <sk/io/Pipe.h>

namespace sk {
  namespace io {
    class AnonymousPipe
      : public virtual sk::io::Pipe
    {
      public:
        AnonymousPipe();
        virtual ~AnonymousPipe();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::io::Pipe implementation.
        void close();
        void closeInput();
        void closeOutput();

        InputStream& inputStream() const;
        OutputStream& outputStream() const;

      private:
        AnonymousPipe(const AnonymousPipe& other);
        AnonymousPipe& operator = (const AnonymousPipe& other);

        sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
        sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
    };
  }
}

#endif /* _SK_IO_ANONYMOUSPIPE_ */

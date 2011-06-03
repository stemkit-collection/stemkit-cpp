/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_LOOSEFILEDESCRIPTOR_
#define _SK_IO_LOOSEFILEDESCRIPTOR_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class LooseFileDescriptor
      : public virtual sk::util::Object 
    {
      public:
        explicit LooseFileDescriptor(int fd);
        LooseFileDescriptor(const LooseFileDescriptor& other);
        virtual ~LooseFileDescriptor();

        int getFileNumber() const;
        
        void close();
        int read(char* buffer, int offset, int length);
        int write(const char* buffer, int offset, int length);
        void inheritable(bool state);

        sk::io::LooseFileDescriptor duplicateLoose() const;
        sk::io::LooseFileDescriptor& reopen(const sk::io::LooseFileDescriptor& other);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
        
      private:
        LooseFileDescriptor& operator = (const LooseFileDescriptor& other);

        int _fd;
    };
  }
}

#endif /* _SK_IO_LOOSEFILEDESCRIPTOR_ */
